#include "CommandLineParser.h"


CommandLineParser::CommandLineParser( int argc, 
                                      char *argv[] )
    : m_currentIndex( 0 )
    , m_useCompiler( false )
    , m_useXml( false )
    , m_briefProgress( false )
    , m_noProgress( false )
    , m_useText( false )
    , m_useCout( false )
{
  for ( int index =1; index < argc; ++index )
  {
    if ( index > 1 )
      m_line += " ";
    m_line += argv[index];
  }
}


CommandLineParser::~CommandLineParser()
{
}


void 
CommandLineParser::parse()
{
  while ( hasNext() )
  {
    getNextOption();
    if ( isOption( "c", "compiler" ) )
      m_useCompiler = true;
    else if ( isOption( "x", "xml" ) )
    {
      m_useXml = true;
      m_xmlFileName = getOptionalParameter();
    }
    else if ( isOption( "s", "xsl" ) )
      m_xsl = getParameter();
    else if ( isOption( "e", "encoding" ) )
      m_encoding = getParameter();
    else if ( isOption( "b", "brief-progress" ) )
      m_briefProgress = true;
    else if ( isOption( "n", "no-progress" ) )
      m_noProgress = true;
    else if ( isOption( "t", "text" ) )
      m_useText = true;
    else if ( isOption( "o", "cout" ) )
      m_useCout = true;
    else if ( !m_option.empty() )
      fail( "Unknown option" );
    else if ( hasNext() )
      readNonOptionCommands();
  }
}


bool 
CommandLineParser::isOption( const std::string &shortName,
                             const std::string &longName )
{
  return (m_option == "-" + shortName)  ||
         (m_option == "--" + longName);
}


bool 
CommandLineParser::hasNext() const
{
  return m_currentIndex < m_line.length();
}


std::string
CommandLineParser::getParameter()
{
  if ( startsWith( "\"" ) )
    return getQuotedParameter();
  else
    return getUnquotedParameter();
}


std::string
CommandLineParser::getUnquotedParameter()
{
  std::string parameter;

  if ( !hasNext() )
    fail( "missing option parameter" );

  while ( hasNext()  &&  !isSpace() )
    parameter += next();
  return parameter;
}


std::string
CommandLineParser::getQuotedParameter()
{
  std::string parameter;
  while ( !startsWith( "\"" ) )
  {
    if ( !hasNext() )
      fail( "Unmatched \" in option parameter" );

    if ( startsWith( "\\" ) )
    {
      skipNext();
      if ( !hasNext() )
        fail( "Missing escaped character in option parameter" );
    }

    parameter += next();
  }
  return parameter;
}


std::string
CommandLineParser::getOptionalParameter()
{
  if ( !hasNext()  ||  startsWith( "-" )  ||  startsWith( ":" ) )
    return "";
  return getParameter();
}


void 
CommandLineParser::getNextOption()
{
  skipSpaces();
  m_option = "";
  if ( startsWith( "-" )  ||  startsWith( "--" ) )
  {
    while ( hasNext()  &&  !isSpace() )
      m_option += next();

    skipSpaces();
  }
}


void 
CommandLineParser::readNonOptionCommands()
{
  if ( startsWith( ":" ) )
  {
    skipNext();
    m_testPath = getParameter();
  }
  else
  {
    CommandLinePlugInInfo plugIn;
    while ( hasNext()  &&  !isSpace()  &&  !startsWith( "=" ) )
      plugIn.m_fileName += next();

    std::string parameters;
    if ( startsWith( "=" ) )
    {
      m_option = plugIn.m_fileName;
      skipNext();
      parameters = getParameter();
    }
    
    plugIn.m_parameters.push_back( parameters );
    m_plugIns.push_back( plugIn );
  }
}


bool 
CommandLineParser::startsWith( const std::string &expected ) const
{
  return m_line.substr( m_currentIndex, expected.length() ) == expected;
}


void 
CommandLineParser::skipSpaces()
{
  while ( hasNext()  &&  isSpace() )
    skipNext();
}


bool 
CommandLineParser::isSpace() const
{
  if ( !hasNext() )
    return true;

  return isSpace( m_line[m_currentIndex] );
}


bool 
CommandLineParser::isSpace( unsigned char c )
{
  return c <= 32;
}


char 
CommandLineParser::next()
{
  if ( !hasNext() )
    fail( "unexpected error while parsing option" );

  return m_line[ m_currentIndex++ ];
}


void 
CommandLineParser::skipNext( int count )
{
  m_currentIndex += count;
  if ( m_currentIndex > m_line.length() )
    m_currentIndex = m_line.length();
}


void 
CommandLineParser::fail( std::string message )
{
  throw CommandLineParserException( "Error while parsing option: " + m_option+
            "\n" + message );
}



bool 
CommandLineParser::useCompilerOutputter() const
{
  return m_useCompiler;
}


bool 
CommandLineParser::useXmlOutputter() const
{
  return m_useXml;
}


std::string 
CommandLineParser::getXmlFileName() const
{
  return m_xmlFileName;
}


std::string 
CommandLineParser::getXmlStyleSheet() const
{
  return m_xsl;
}


std::string 
CommandLineParser::getEncoding() const
{
  return m_encoding;
}


bool 
CommandLineParser::useBriefTestProgress() const
{
  return m_briefProgress;
}


bool 
CommandLineParser::noTestProgress() const
{
  return m_noProgress;
}


bool 
CommandLineParser::useTextOutputter() const
{
  return m_useText;
}


bool 
CommandLineParser::useCoutStream() const
{
  return m_useCout;
}


int 
CommandLineParser::getPlugInCount() const
{
  return m_plugIns.size(); 
}

CommandLinePlugInInfo 
CommandLineParser::getPlugInAt( int index ) const
{
  return m_plugIns.at( index );
}


std::string 
CommandLineParser::getTestPath() const
{
  return m_testPath;
}


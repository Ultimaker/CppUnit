#include <cppunit/Exception.h>
#include <cppunit/SourceLine.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>
#include <algorithm>


namespace CppUnit
{

CompilerOutputter::CompilerOutputter( TestResultCollector *result,
                                      std::ostream &stream,
                                      const std::string &locationFormat )
    : m_result( result )
    , m_stream( stream )
    , m_locationFormat( locationFormat )
{
}


CompilerOutputter::~CompilerOutputter()
{
}


void 
CompilerOutputter::setLocationFormat( const std::string &locationFormat )
{
  m_locationFormat = locationFormat;
}


CompilerOutputter *
CompilerOutputter::defaultOutputter( TestResultCollector *result,
                                     std::ostream &stream )
{
  return new CompilerOutputter( result, stream );
}


void 
CompilerOutputter::write()
{
  if ( m_result->wasSuccessful() )
    printSuccess();
  else
    printFailureReport();
}


void 
CompilerOutputter::printSuccess()
{
  m_stream  << "OK (" << m_result->runTests()  << ")"  
            <<  std::endl;
}


void 
CompilerOutputter::printFailureReport()
{
  printFailuresList();
  printStatistics();
}


void 
CompilerOutputter::printFailuresList()
{
  for ( int index =0; index < m_result->testFailuresTotal(); ++index)
  {
    printFailureDetail( m_result->failures()[ index ] );
  }
}


void 
CompilerOutputter::printFailureDetail( TestFailure *failure )
{
  printFailureLocation( failure->sourceLine() );
  printFailureType( failure );
  printFailedTestName( failure );
  printFailureMessage( failure );
}

 
void 
CompilerOutputter::printFailureLocation( SourceLine sourceLine )
{
  if ( !sourceLine.isValid() )
  {
    m_stream  <<  "##Failure Location unknown## : ";
    return;
  }

  std::string location;
  for ( int index = 0; index < m_locationFormat.length(); ++index )
  {
    char c = m_locationFormat[ index ];
    if ( c == '%'  &&  ( index+1 < m_locationFormat.length() ) )
    {
      char command = m_locationFormat[index+1];
      if ( processLocationFormatCommand( command, sourceLine ) )
      {
        ++index;
        continue;
      }
    }

    m_stream  << c;
  }
}


bool 
CompilerOutputter::processLocationFormatCommand( char command, 
                                                 const SourceLine &sourceLine )
{
  switch ( command )
  {
  case 'p':
    m_stream  <<  sourceLine.fileName();
    return true;
  case 'l':
    m_stream  <<  sourceLine.lineNumber();
    return true;
  case 'f':
    m_stream  <<  extractBaseName( sourceLine.fileName() );
    return true;
  }
  
  return false;
}


std::string 
CompilerOutputter::extractBaseName( const std::string &fileName ) const
{
  int indexLastDirectorySeparator = fileName.find_last_of( '/' );
  
  if ( indexLastDirectorySeparator < 0 )
    indexLastDirectorySeparator = fileName.find_last_of( '\\' );
  
  if ( indexLastDirectorySeparator < 0 )
    return fileName;

  return fileName.substr( indexLastDirectorySeparator +1 );
}


void 
CompilerOutputter::printFailureType( TestFailure *failure )
{
  m_stream  <<  (failure->isError() ? "Error" : "Assertion");
}


void 
CompilerOutputter::printFailedTestName( TestFailure *failure )
{
  m_stream  <<  std::endl;
  m_stream  <<  "Test name: "  <<  failure->failedTestName();
}


void 
CompilerOutputter::printFailureMessage( TestFailure *failure )
{
  m_stream  <<  std::endl;
  Exception *thrownException = failure->thrownException();
  m_stream  << thrownException->message().shortDescription()  <<  std::endl;
  m_stream  <<  wrap( thrownException->message().details() )  <<  std::endl;
}


void 
CompilerOutputter::printStatistics()
{
  m_stream  <<  "Failures !!!"  <<  std::endl;
  m_stream  <<  "Run: "  <<  m_result->runTests()  << "   "
            <<  "Failure total: "  <<  m_result->testFailuresTotal()  << "   "
            <<  "Failures: "  <<  m_result->testFailures()  << "   "
            <<  "Errors: "  <<  m_result->testErrors()
            <<  std::endl;
}


std::string
CompilerOutputter::wrap( std::string message )
{
  Lines lines = splitMessageIntoLines( message );
  std::string wrapped;
  for ( Lines::iterator it = lines.begin(); it != lines.end(); ++it )
  {
    std::string line( *it );
    const int maxLineLength = 80;
    int index =0;
    while ( index < line.length() )
    {
      std::string line( line.substr( index, maxLineLength ) );
      wrapped += line;
      index += maxLineLength;
      if ( index < line.length() )
        wrapped += "\n";
    }
    wrapped += '\n';
  }
  return wrapped;
}


CompilerOutputter::Lines 
CompilerOutputter::splitMessageIntoLines( std::string message )
{
  Lines lines;

  std::string::iterator itStart = message.begin();
  while ( true )
  {
    std::string::iterator itEol = std::find( itStart, 
                                             message.end(), 
                                             '\n' );
    lines.push_back( message.substr( itStart - message.begin(),
                                     itEol - itStart ) );
    if ( itEol == message.end() )
      break;
    itStart = itEol +1;
  }
  return lines;
}



}  // namespace CppUnit

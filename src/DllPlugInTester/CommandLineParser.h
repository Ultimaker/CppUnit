#ifndef CPPUNIT_HELPER_COMMANDLINEPARSER_H
#define CPPUNIT_HELPER_COMMANDLINEPARSER_H

#include <cppunit/Portability.h>
#include <cppunit/plugin/Parameters.h>
#include <string>
#include <stdexcept>
#include <deque>


/*! Exception thrown on error while parsing command line.
 */
class CommandLineParserException : public std::runtime_error
{
public:
  CommandLineParserException( std::string message )
    : std::runtime_error( message )
  {
  }
};


struct CommandLinePlugInInfo
{
  std::string m_fileName;
  CppUnit::Parameters m_parameters;
};


/*! \brief Parses a command line.

-c --compiler
-x --xml [filename]
-s --xsl stylesheet
-e --encoding encoding
-b --brief-progress
-n --no-progress
-t --text
-o --cout
filename[="options"]
:testpath

 */
class CommandLineParser
{
public:
  /*! Constructs a CommandLineParser object.
   */
  CommandLineParser( int argc, 
                     char *argv[] );

  /// Destructor.
  virtual ~CommandLineParser();

  /*! Parses the command line.
   * \exception CommandLineParserException if an error occurs.
   */
  void parse();

  bool useCompilerOutputter() const;
  bool useXmlOutputter() const;
  std::string getXmlFileName() const;
  std::string getXmlStyleSheet() const;
  std::string getEncoding() const;
  bool useBriefTestProgress() const;
  bool noTestProgress() const;
  bool useTextOutputter() const;
  bool useCoutStream() const;
  std::string getTestPath() const;
  int getPlugInCount() const;
  CommandLinePlugInInfo getPlugInAt( int index ) const;

protected:
  /// Prevents the use of the copy constructor.
  CommandLineParser( const CommandLineParser &copy );

  /// Prevents the use of the copy operator.
  void operator =( const CommandLineParser &copy );

  bool isOption( const std::string &shortName,
                 const std::string &longName );

  bool hasNext() const;
  bool startsWith( const std::string &expected ) const;
  char next();
  void skipNext( int count =1 );
  bool isSpace() const;

  std::string getParameter();
  std::string getQuotedParameter();
  std::string getUnquotedParameter();
  std::string getOptionalParameter();
  void fail( std::string message );
  void getNextOption();
  void skipSpaces();
  static bool isSpace( unsigned char c );

  void readNonOptionCommands();

protected:
  std::string m_line;
  int m_currentIndex;
  std::string m_option;

  bool m_useCompiler;
  bool m_useXml;
  std::string m_xmlFileName;
  std::string m_xsl;
  std::string m_encoding;
  bool m_briefProgress;
  bool m_noProgress;
  bool m_useText;
  bool m_useCout;
  std::string m_testPath;

  typedef std::deque<CommandLinePlugInInfo> PlugIns;
  PlugIns m_plugIns;
};


#endif  // CPPUNIT_HELPER_COMMANDLINEPARSER_H

#ifndef CPPUNIT_XMLTESTRESULTOUTPUTTER_H
#define CPPUNIT_XMLTESTRESULTOUTPUTTER_H

#include <cppunit/Portability.h>

#if CPPUNIT_NEED_DLL_DECL
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#endif

#include <cppunit/Outputter.h>
#include <iostream>
#include <map>


namespace CppUnit
{

class Test;
class TestFailure;
class TestResultCollector;
class XmlDocument;
class XmlElement;


/*! \brief Outputs a TestResultCollector in XML format.
 * \ingroup WritingTestResult
 */
class CPPUNIT_API XmlOutputter : public Outputter
{
public:
  /*! Constructs a XmlOutputter object.
   * \param result Result of the test run.
   * \param stream Stream used to output the XML output.
   * \param encoding Encoding used in the XML file (default is Latin-1). 
   */
  XmlOutputter( TestResultCollector *result,
                std::ostream &stream,
                std::string encoding = "ISO-8859-1" );

  /// Destructor.
  virtual ~XmlOutputter();

  /*! Writes the specified result as an XML document to the stream.
   *
   * Refer to examples/cppunittest/XmlOutputterTest.cpp for example
   * of use and XML document structure.
   */
  virtual void write();

  /*! Sets the XSL style sheet used.
   *
   * \param styleSheet Name of the style sheet used. If empty, then no style sheet
   *                   is used (default).
   */
  virtual void setStyleSheet( const std::string &styleSheet );


  typedef std::map<Test *,TestFailure*> FailedTests;
  virtual XmlElement *makeRootNode();
  virtual void addFailedTests( FailedTests &failedTests,
                               XmlElement *rootNode );
  virtual void addSuccessfulTests( FailedTests &failedTests,
                                   XmlElement *rootNode );
  virtual void addStatistics( XmlElement *rootNode );
  virtual void addFailedTest( Test *test,
                              TestFailure *failure,
                              int testNumber,
                              XmlElement *testsNode );
  virtual void addFailureLocation( TestFailure *failure,
                                   XmlElement *testNode );
  virtual void addSuccessfulTest( Test *test, 
                                  int testNumber,
                                  XmlElement *testsNode );
protected:
  virtual void fillFailedTestsMap( FailedTests &failedTests );

protected:
  TestResultCollector *m_result;
  std::ostream &m_stream;
  std::string m_encoding;
  std::string m_styleSheet;
  XmlDocument *m_xml;

private:
  /// Prevents the use of the copy constructor.
  XmlOutputter( const XmlOutputter &copy );

  /// Prevents the use of the copy operator.
  void operator =( const XmlOutputter &copy );

private:
};



}  // namespace CppUnit


#if CPPUNIT_NEED_DLL_DECL
#pragma warning( pop )
#endif

#endif  // CPPUNIT_XMLTESTRESULTOUTPUTTER_H

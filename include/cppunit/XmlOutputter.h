#ifndef CPPUNIT_XMLTESTRESULTOUTPUTTER_H
#define CPPUNIT_XMLTESTRESULTOUTPUTTER_H

#include <cppunit/Portability.h>

#if CPPUNIT_NEED_DLL_DECL
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#endif

#include <cppunit/Outputter.h>
#include <deque>
#include <iostream>
#include <map>


namespace CppUnit
{

class Test;
class TestFailure;
class TestResultCollector;
class XmlDocument;
class XmlElement;
class XmlOutputterHook;


/*! \brief Outputs a TestResultCollector in XML format.
 * \ingroup WritingTestResult
 *
 * Save the test result as a XML stream. 
 *
 * Additional datas can be added to the XML document using XmlOutputterHook. 
 * Hook are not owned by the XmlOutputter. They should be valid until 
 * destruction of the XmlOutputter. They can be removed with removeHook().
 *
 * \see XmlDocument, XmlElement, XmlOutputterHook.
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
                std::string encoding = std::string("ISO-8859-1") );

  /// Destructor.
  virtual ~XmlOutputter();

  /*! Adds the specified hook to the outputter.
   * \param hook Hook to add. Must not be \c NULL.
   */
  virtual void addHook( XmlOutputterHook *hook );

  /*! Removes the specified hook from the outputter.
   * \param hook Hook to remove.
   */
  virtual void removeHook( XmlOutputterHook *hook );

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

  /*! Sets the root element and adds its children.
   *
   * Set the root element of the XML Document and add its child elements.
   *
   * For all hooks, call beginDocument() just after creating the root element (it
   * is empty at this time), and endDocument() once all the datas have been added
   * to the root element.
   */
  virtual void setRootNode();

  virtual void addFailedTests( FailedTests &failedTests,
                               XmlElement *rootNode );

  virtual void addSuccessfulTests( FailedTests &failedTests,
                                   XmlElement *rootNode );

  /*! Adds the statics element to the root node.
   * 
   * Creates a new element containing statistics data and adds it to the root element.
   * Then, for all hooks, call statisticsAdded().
   * \param rootNode Root element.
   */
  virtual void addStatistics( XmlElement *rootNode );

  /*! Adds a failed test to the failed tests node.
   * Creates a new element containing datas about the failed test, and adds it to 
   * the failed tests element.
   * Then, for all hooks, call failTestAdded().
   */
  virtual void addFailedTest( Test *test,
                              TestFailure *failure,
                              int testNumber,
                              XmlElement *testsNode );

  virtual void addFailureLocation( TestFailure *failure,
                                   XmlElement *testElement );


  /*! Adds a successful test to the successful tests node.
   * Creates a new element containing datas about the successful test, and adds it to 
   * the successful tests element.
   * Then, for all hooks, call successfulTestAdded().
   */
  virtual void addSuccessfulTest( Test *test, 
                                  int testNumber,
                                  XmlElement *testsNode );
protected:
  virtual void fillFailedTestsMap( FailedTests &failedTests );

protected:
  typedef std::deque<XmlOutputterHook *> Hooks;

  TestResultCollector *m_result;
  std::ostream &m_stream;
  std::string m_encoding;
  std::string m_styleSheet;
  XmlDocument *m_xml;
  Hooks m_hooks;

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

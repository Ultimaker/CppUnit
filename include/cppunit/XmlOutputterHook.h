#ifndef CPPUNIT_XMLOUTPUTTERHOOK_H
#define CPPUNIT_XMLOUTPUTTERHOOK_H

#include <cppunit/Portability.h>


namespace CppUnit
{

class Test;
class TestFailure;
class XmlDocument;
class XmlElement;



/*! \brief Hook to customize Xml output.
 *
 * XmlOutputterHook can be passed to XmlOutputter to customize the XmlDocument.
 *
 * Common customizations are:
 * - adding some datas to successfull or failed test with
 *   failTestAdded() and successfulTestAdded(),
 * - adding some statistics with statisticsAdded(),
 * - adding other datas with beginDocument() or endDocument().
 *
 * See examples/ClockerPlugIn which makes use of most the hook.
 *
 * %Test plug-ins can also implement hook to customize XML output.
 *
 * \see XmlOutputter, CppUnitTestPlugIn.
 */
class CPPUNIT_API XmlOutputterHook
{
public:
  /*! Called before any elements is added to the root element.
   * \param document XML Document being created.
   */
  virtual void beginDocument( XmlDocument *document );

  /*! Called after adding all elements to the root element.
   * \param document XML Document being created.
   */
  virtual void endDocument( XmlDocument *document );

  /*! Called after adding a fail test element.
   * \param document XML Document being created.
   * \param testElement <FailedTest> element.
   * \param test Test that failed.
   * \param failure Test failure data.
   */
  virtual void failTestAdded( XmlDocument *document,
                              XmlElement *testElement,
                              Test *test,
                              TestFailure *failure );

  /*! Called after adding a successful test element.
   * \param document XML Document being created.
   * \param testElement <Test> element.
   * \param test Test that was successful.
   */
  virtual void successfulTestAdded( XmlDocument *document,
                                    XmlElement *testElement,
                                    Test *test );

  /*! Called after adding the statistic element.
   * \param document XML Document being created.
   * \param statisticsElement <Statistics> element.
   */
  virtual void statisticsAdded( XmlDocument *document,
                                XmlElement *statisticsElement );
};



} //  namespace CppUnit


#endif  // CPPUNIT_XMLOUTPUTTERHOOK_H

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
 */
class CPPUNIT_API XmlOutputterHook
{
public:
  virtual void beginDocument( XmlDocument *document,
                              XmlElement *rootNode );

  virtual void endDocument( XmlDocument *document,
                            XmlElement *rootNode );

  virtual void failTestAdded( XmlDocument *document,
                              XmlElement *testNode,
                              Test *test,
                              TestFailure *failure );

  virtual void successfulTestAdded( XmlDocument *document,
                                    XmlElement *testNode,
                                    Test *test );

  virtual void statisticsAdded( XmlDocument *document,
                                XmlElement *statisticsNode );
};



} //  namespace CppUnit


#endif  // CPPUNIT_XMLOUTPUTTERHOOK_H

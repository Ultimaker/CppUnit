#include <cppunit/XmlOutputterHook.h>


namespace CppUnit
{


void 
XmlOutputterHook::beginDocument( XmlDocument *document,
                                 XmlElement *rootNode )
{
}


void 
XmlOutputterHook::endDocument( XmlDocument *document,
                               XmlElement *rootNode )
{
}


void 
XmlOutputterHook::failTestAdded( XmlDocument *document,
                                 XmlElement *testNode,
                                 Test *test,
                                 TestFailure *failure )
{
}


void 
XmlOutputterHook::successfulTestAdded( XmlDocument *document,
                                       XmlElement *testNode,
                                       Test *test )
{
}


void 
XmlOutputterHook::statisticsAdded( XmlDocument *document,
                                   XmlElement *statisticsNode )
{
}


} //  namespace CppUnit


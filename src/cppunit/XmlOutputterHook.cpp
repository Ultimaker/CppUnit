#include <cppunit/XmlOutputterHook.h>


namespace CppUnit
{


void 
XmlOutputterHook::beginDocument( XmlDocument *document )
{
}


void 
XmlOutputterHook::endDocument( XmlDocument *document )
{
}


void 
XmlOutputterHook::failTestAdded( XmlDocument *document,
                                 XmlElement *testElement,
                                 Test *test,
                                 TestFailure *failure )
{
}


void 
XmlOutputterHook::successfulTestAdded( XmlDocument *document,
                                       XmlElement *testElement,
                                       Test *test )
{
}


void 
XmlOutputterHook::statisticsAdded( XmlDocument *document,
                                   XmlElement *statisticsElement )
{
}


} //  namespace CppUnit


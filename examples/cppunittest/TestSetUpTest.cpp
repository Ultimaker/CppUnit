#include "ExtensionSuite.h"
#include "TestSetUpTest.h"
#include <cppunit/TestResult.h>

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestSetUpTest,
                                       extensionSuiteName() );


TestSetUpTest::TestSetUpTest()
{
}


TestSetUpTest::~TestSetUpTest()
{
}


void 
TestSetUpTest::setUp()
{
}


void 
TestSetUpTest::tearDown()
{
}


void 
TestSetUpTest::testRun()
{
  CPPUNIT_NS::TestResult result;
  CPPUNIT_NS::TestCase test;
  MockSetUp setUpTest( &test );
  
  setUpTest.run( &result );

  setUpTest.verify();
}

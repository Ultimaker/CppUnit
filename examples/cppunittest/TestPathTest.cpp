#include "CoreSuite.h"
#include "TestPathTest.h"


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestPathTest,
                                       CppUnitTest::coreSuiteName() );


TestPathTest::TestPathTest()
{
}


TestPathTest::~TestPathTest()
{
}


void 
TestPathTest::setUp()
{
  m_path = new CppUnit::TestPath();
  m_test1 = new CppUnit::TestCase( "test1" );
  m_test2 = new CppUnit::TestCase( "test2" );
  m_test3 = new CppUnit::TestCase( "test3" );
  m_test4 = new CppUnit::TestCase( "test4" );

  m_suite1 = new CppUnit::TestSuite( "All Tests" );
  m_suite2 = new CppUnit::TestSuite( "Custom" );
  m_testSuite2a =  new CppUnit::TestCase( "MyTest::testDefaultConstructor" );
  m_testSuite2b =  new CppUnit::TestCase( "MyTest::testConstructor" );
  m_suite2->addTest( m_testSuite2a );
  m_suite2->addTest( m_testSuite2b );
  m_suite1->addTest( m_suite2 );
}


void 
TestPathTest::tearDown()
{
  delete m_suite1;
  delete m_path;
  delete m_test4;
  delete m_test3;
  delete m_test2;
  delete m_test1;
}


void 
TestPathTest::testDefaultConstructor()
{
  CPPUNIT_ASSERT_EQUAL( 0, m_path->getTestCount() );
  CPPUNIT_ASSERT( !m_path->isValid() );
}


void 
TestPathTest::testAddTest()
{
  m_path->add( m_test1 );
  CPPUNIT_ASSERT_EQUAL( 1, m_path->getTestCount() );
  CPPUNIT_ASSERT( m_path->isValid() );
  CPPUNIT_ASSERT( m_test1 == m_path->getTestAt(0) );
}


void 
TestPathTest::testGetTestAtThrow1()
{
  m_path->getTestAt( 0 );
}


void 
TestPathTest::testGetTestAtThrow2()
{
  m_path->add( m_test1 );
  m_path->getTestAt( 1 );
}


void 
TestPathTest::testGetChildTest()
{
  m_path->add( m_test1 );
  CPPUNIT_ASSERT( m_test1 == m_path->getChildTest() );
}


void 
TestPathTest::testGetChildTestManyTests()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );
  m_path->add( m_test3 );
  CPPUNIT_ASSERT( m_test3 == m_path->getChildTest() );
}


void 
TestPathTest::testGetChildTestThrowIfNotValid()
{
  m_path->getChildTest();
}


void 
TestPathTest::testAddPath()
{
  CppUnit::TestPath path;
  path.add( m_test2 );
  path.add( m_test3 );

  m_path->add( m_test1 );
  m_path->add( path );

  CPPUNIT_ASSERT_EQUAL( 3, m_path->getTestCount() );
  CPPUNIT_ASSERT( m_test1 == m_path->getTestAt(0) );
  CPPUNIT_ASSERT( m_test2 == m_path->getTestAt(1) );
  CPPUNIT_ASSERT( m_test3 == m_path->getTestAt(2) );
}


void 
TestPathTest::testAddInvalidPath()
{
  CppUnit::TestPath path;
  m_path->add( path );

  CPPUNIT_ASSERT( !m_path->isValid() );
}


void 
TestPathTest::testRemoveTests()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );

  m_path->removeTests();

  CPPUNIT_ASSERT( !m_path->isValid() );
}


void 
TestPathTest::testRemoveTest()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );

  m_path->removeTest( 0 );

  CPPUNIT_ASSERT_EQUAL( 1, m_path->getTestCount() );
  CPPUNIT_ASSERT( m_test2 == m_path->getTestAt(0) );
}


void 
TestPathTest::testRemoveTestThrow1()
{
  m_path->removeTest( -1 );
}


void 
TestPathTest::testRemoveTestThrow2()
{
  m_path->add( m_test1 );

  m_path->removeTest( 1 );
}


void 
TestPathTest::testUp()
{
  m_path->add( m_test1 );

  m_path->up();

  CPPUNIT_ASSERT( !m_path->isValid() );
}


void 
TestPathTest::testUpThrow()
{
  m_path->up();
}


void 
TestPathTest::testInsert()
{
  m_path->add( m_test1 );

  m_path->insert( m_test2, 0 );

  CPPUNIT_ASSERT_EQUAL( 2, m_path->getTestCount() );
  CPPUNIT_ASSERT( m_test2 == m_path->getTestAt(0) );
  CPPUNIT_ASSERT( m_test1 == m_path->getTestAt(1) );
}


void 
TestPathTest::testInsertAtEnd()
{
  m_path->add( m_test1 );

  m_path->insert( m_test2, 1 );

  CPPUNIT_ASSERT_EQUAL( 2, m_path->getTestCount() );
  CPPUNIT_ASSERT( m_test1 == m_path->getTestAt(0) );
  CPPUNIT_ASSERT( m_test2 == m_path->getTestAt(1) );
}


void 
TestPathTest::testInsertThrow1()
{
  m_path->insert( m_test1, -1 );
}


void 
TestPathTest::testInsertThrow2()
{
  m_path->add( m_test1 );

  m_path->insert( m_test1, 2 );
}


void 
TestPathTest::testInsertPath()
{
  CppUnit::TestPath path;
  path.add( m_test2 );
  path.add( m_test3 );

  m_path->add( m_test1 );
  m_path->add( m_test4 );
  m_path->insert( path, 1 );

  CPPUNIT_ASSERT_EQUAL( 4, m_path->getTestCount() );
  CPPUNIT_ASSERT( m_test1 == m_path->getTestAt(0) );
  CPPUNIT_ASSERT( m_test2 == m_path->getTestAt(1) );
  CPPUNIT_ASSERT( m_test3 == m_path->getTestAt(2) );
  CPPUNIT_ASSERT( m_test4 == m_path->getTestAt(3) );
}


void 
TestPathTest::testInsertPathThrow()
{
  CppUnit::TestPath path;
  path.add( m_test2 );

  m_path->insert( path, 1 );
}


void 
TestPathTest::testInsertPathDontThrowIfInvalid()
{
  CppUnit::TestPath path;
  m_path->insert( path, 1 );
}


void 
TestPathTest::testRootConstructor()
{
  CppUnit::TestPath path( m_test1 );
  CPPUNIT_ASSERT( path.isValid() );
  CPPUNIT_ASSERT_EQUAL( 1, path.getTestCount() );
  CPPUNIT_ASSERT( m_test1 == path.getTestAt(0) );
}


void 
TestPathTest::testPathSliceConstructorCopyUntilEnd()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );
  m_path->add( m_test3 );
  
  CppUnit::TestPath path( *m_path, 1 );

  CPPUNIT_ASSERT_EQUAL( 2, path.getTestCount() );
  CPPUNIT_ASSERT( m_test2 == path.getTestAt(0) );
  CPPUNIT_ASSERT( m_test3 == path.getTestAt(1) );
}


void 
TestPathTest::testPathSliceConstructorCopySpecifiedCount()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );
  m_path->add( m_test3 );
  
  CppUnit::TestPath path( *m_path, 0, 1 );

  CPPUNIT_ASSERT_EQUAL( 1, path.getTestCount() );
  CPPUNIT_ASSERT( m_test1 == path.getTestAt(0) );
}


void 
TestPathTest::testPathSliceConstructorCopyNone()
{
  m_path->add( m_test1 );
  
  CppUnit::TestPath path( *m_path, 0, 0 );
  CPPUNIT_ASSERT_EQUAL( 0, path.getTestCount() );
}


void 
TestPathTest::testPathSliceConstructorNegativeIndex()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );

  CppUnit::TestPath path( *m_path, -1, 2 );

  CPPUNIT_ASSERT_EQUAL( 1, path.getTestCount() );
  CPPUNIT_ASSERT( m_test1 == path.getTestAt(0) );
}


void 
TestPathTest::testPathSliceConstructorAfterEndIndex()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );

  CppUnit::TestPath path( *m_path, 2, 5 );

  CPPUNIT_ASSERT_EQUAL( 0, path.getTestCount() );
}


void 
TestPathTest::testPathSliceConstructorNegativeIndexUntilEnd()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );

  CppUnit::TestPath path( *m_path, -1 );

  CPPUNIT_ASSERT_EQUAL( 2, path.getTestCount() );
  CPPUNIT_ASSERT( m_test1 == path.getTestAt(0) );
  CPPUNIT_ASSERT( m_test2 == path.getTestAt(1) );
}


void 
TestPathTest::testPathSliceConstructorNegativeIndexNone()
{
  m_path->add( m_test1 );
  m_path->add( m_test2 );

  CppUnit::TestPath path( *m_path, -2, 1 );

  CPPUNIT_ASSERT_EQUAL( 0, path.getTestCount() );
}


void 
TestPathTest::testToStringNoTest()
{
  std::string expected = "/";
  std::string actual = m_path->toString();

  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
TestPathTest::testToStringOneTest()
{
  m_path->add( m_test1 );

  std::string expected = "/test1";
  std::string actual = m_path->toString();

  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
TestPathTest::testToStringHierarchy()
{
  m_path->add( m_suite1 );
  m_path->add( m_suite2 );
  m_path->add( m_suite2->getChildTestAt(0) );

  std::string expected = "/All Tests/Custom/MyTest::testDefaultConstructor";
  std::string actual = m_path->toString();

  CPPUNIT_ASSERT_EQUAL( expected, actual );
}


void 
TestPathTest::testPathStringConstructorRoot()
{
  CppUnit::TestPath path( m_suite1, "/All Tests" );

  CPPUNIT_ASSERT_EQUAL( 1, path.getTestCount() );
  CPPUNIT_ASSERT( m_suite1 == path.getTestAt(0) );
}


void 
TestPathTest::testPathStringConstructorEmptyIsRoot()
{
  CppUnit::TestPath path( m_suite1, "" );

  CPPUNIT_ASSERT_EQUAL( 1, path.getTestCount() );
  CPPUNIT_ASSERT( m_suite1 == path.getTestAt(0) );
}


void 
TestPathTest::testPathStringConstructorHierarchy()
{
  CppUnit::TestPath path( m_suite1, "/All Tests/Custom/MyTest::testDefaultConstructor" );

  CPPUNIT_ASSERT_EQUAL( 3, path.getTestCount() );
  CPPUNIT_ASSERT( m_suite1 == path.getTestAt(0) );
  CPPUNIT_ASSERT( m_suite2 == path.getTestAt(1) );
  CPPUNIT_ASSERT( m_testSuite2a == path.getTestAt(2) );
}


void 
TestPathTest::testPathStringConstructorBadRootThrow()
{
  CppUnit::TestPath path( m_suite1, "/Custom" );
}


void 
TestPathTest::testPathStringConstructorRelativeRoot()
{
  CppUnit::TestPath path( m_suite1, "All Tests" );

  CPPUNIT_ASSERT_EQUAL( 1, path.getTestCount() );
  CPPUNIT_ASSERT( m_suite1 == path.getTestAt(0) );
}


void 
TestPathTest::testPathStringConstructorRelativeRoot2()
{
  CppUnit::TestPath path( m_suite1, "Custom" );

  CPPUNIT_ASSERT_EQUAL( 1, path.getTestCount() );
  CPPUNIT_ASSERT( m_suite2 == path.getTestAt(0) );
}


void 
TestPathTest::testPathStringConstructorThrow1()
{
  CppUnit::TestPath path( m_suite1, "/" );
}


void 
TestPathTest::testPathStringConstructorRelativeHierarchy()
{
  CppUnit::TestPath path( m_suite1, "Custom/MyTest::testConstructor" );

  CPPUNIT_ASSERT_EQUAL( 2, path.getTestCount() );
  CPPUNIT_ASSERT( m_suite2 == path.getTestAt(0) );
  CPPUNIT_ASSERT( m_testSuite2b == path.getTestAt(1) );
}


void 
TestPathTest::testPathStringConstructorBadRelativeHierarchyThrow()
{
  CppUnit::TestPath path( m_suite1, "Custom/MyBadTest::testConstructor" );
}

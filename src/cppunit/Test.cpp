#include <cppunit/Portability.h>
#include <cppunit/Test.h>
#include <cppunit/TestPath.h>
#include <stdexcept>


namespace CppUnit {

Test *
Test::getChildTestAt( int index ) const
{
  checkIsValidIndex( index );
  return doGetChildTestAt( index );
}


Test *
Test::findTest( const std::string &testName ) const
{
  TestPath path;
  // since path is discarded, it is really a const method.
  const_cast<Test *>(this)->findTestPath( testName, path );
  if ( !path.isValid() )
    throw std::invalid_argument( "No test named <" + testName + "> found in test <"
                                 + getName() + ">." );
  return path.getChildTest();
}


bool 
Test::findTestPath( const std::string &testName,
                    TestPath &testPath )
{
  if ( getName() == testName )
  {
    testPath.add( this );
    return true;
  }

  int childCount = getChildTestCount();
  for ( int childIndex =0; childIndex < childCount; ++childIndex )
  {
    if ( getChildTestAt( childIndex )->findTestPath( testName, testPath ) )
    {
      testPath.insert( this, 0 );
      return true;
    }
  }

  return false;
}


bool 
Test::findTestPath( const Test *test,
                    TestPath &testPath )
{
  if ( this == test )
  {
    testPath.add( this );
    return true;
  }

  int childCount = getChildTestCount();
  for ( int childIndex =0; childIndex < childCount; ++childIndex )
  {
    if ( getChildTestAt( childIndex )->findTestPath( test, testPath ) )
    {
      testPath.insert( this, 0 );
      return true;
    }
  }

  return false;
}


TestPath 
Test::resolveTestPath( const std::string &testPath )
{
  return TestPath( this, testPath );
}


void 
Test::checkIsValidIndex( int index ) const
{
  if ( index < 0  ||  index >= getChildTestCount() )
    throw std::out_of_range( "Test::checkValidIndex(): invalid index" );
}
  

} // namespace CppUnit

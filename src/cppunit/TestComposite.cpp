#include <cppunit/TestComposite.h>
#include <cppunit/TestResult.h>


namespace CppUnit {

TestComposite::TestComposite( const std::string &name )
    : m_name( name )
{
}


TestComposite::~TestComposite()
{
}


void 
TestComposite::run( TestResult *result )
{
  int childCount = getChildTestCount();
  for ( int index =0; index < childCount; ++index )
  {
    if ( result->shouldStop() )
      break;

    getChildTestAt( index )->run( result );
  }
}


int 
TestComposite::countTestCases() const
{
  int count = 0;
  
  int childCount = getChildTestCount();
  for ( int index =0; index < childCount; ++index )
    count += getChildTestAt( index )->countTestCases();
  
  return count;
}


std::string 
TestComposite::getName() const
{
  return m_name;
}


} // namespace CppUnit


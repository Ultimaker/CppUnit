#include <cppunit/Portability.h>
#include "cppunit/TestRegistry.h"
#include "cppunit/Test.h"

namespace CppUnit {

TestRegistry&
TestRegistry::getRegistry ()
{
  static TestRegistry registry; // instantiated on first call of getRegistry().
  return registry;              
}

void 
TestRegistry::addTest(std::string name, Test *test)
{ 
  getRegistry().m_registry_names.push_back (name);
  getRegistry().m_registry_tests.push_back (test); 
}

const std::vector<std::string>&
TestRegistry::getAllTestNames () const
{
  return getRegistry().m_registry_names;
}

const std::vector<Test*>& 
TestRegistry::getAllTests() const
{
  return getRegistry().m_registry_tests;
}

std::vector<Test*> 
TestRegistry::getTest (const std::string& testCase) const
{
  std::vector<Test*> res;
  std::vector<Test*>::iterator test_it;
  std::vector<std::string>::iterator name_it;
  for (test_it = getRegistry().m_registry_tests.begin (),
       name_it = getRegistry().m_registry_names.begin ();
       test_it != getRegistry().m_registry_tests.end ();
       ++test_it, ++name_it) {
    if ((*name_it) == testCase) {
      res.push_back((*test_it));
      break;
    }
  }
  return(res);
}

TestRegistry::~TestRegistry ()
{
    for (std::vector<Test*>::iterator it = m_registry_tests.begin ();
         it != m_registry_tests.end ();
         ++it) {
        delete *it;
    }
}

TestRegistry::TestRegistry ()
{
}

} // namespace CppUnit


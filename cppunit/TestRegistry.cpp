#include "TestRegistry.h"
#include "Test.h"

//using namespace std;

namespace CppUnit {

std::vector<std::string> s_registry_names;
std::vector<Test*> s_registry_tests;

static TestRegistry* s_registry;
static bool instanciated=false;

TestRegistry&
TestRegistry::getRegistry ()
{
  if(!instanciated) {
    s_registry=new TestRegistry();
    instanciated=true;
  }
  return *s_registry;
}

void 
TestRegistry::addTest(std::string name, Test *test)
{ 
  s_registry_names.push_back (name);
  s_registry_tests.push_back (test); 
}

const std::vector<std::string>&
TestRegistry::getAllTestNames () const
{
  return(s_registry_names);
}

const std::vector<Test*>& 
TestRegistry::getAllTests() const
{
  return(s_registry_tests);
}

std::vector<Test*> 
TestRegistry::getTest (const std::string& testCase) const
{
  std::vector<Test*> res;
  std::vector<Test*>::iterator test_it;
  std::vector<std::string>::iterator name_it;
  for (test_it = s_registry_tests.begin (),
       name_it = s_registry_names.begin ();
       test_it != s_registry_tests.end ();
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
    for (std::vector<Test*>::iterator it = s_registry_tests.begin ();
             it != s_registry_tests.end ();
             ++it)
        delete *it;
}

TestRegistry::TestRegistry ()
{
}

} // namespace CppUnit


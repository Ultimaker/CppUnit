#include "cppunit/TestRegistry.h"
#include "cppunit/TextTestResult.h"
#include "cppunit/TestSuite.h"
#include "cppunit/Test.h"

#include "BoardGame.h"
#include "Chess.h"

#include "BoardGameTest.h"
#include "ChessTest.h"


#include <vector>
#include <iostream>

BoardGameTest<BoardGame> bgt("BoardGameTest<BoardGame>");
ChessTest<Chess> ct("ChessTest<Chess>");


int 
main(int argc, char** argv)
{
  CppUnit::TextTestResult res;
  CppUnit::TestSuite suite;

  bgt.registerTests(&suite);
  ct.registerTests(&suite);

  std::vector<CppUnit::Test*> tests = 
      CppUnit::TestRegistry::getRegistry().getAllTests();

  for(std::vector<CppUnit::Test*>::iterator it=tests.begin();
      it!=tests.end(); ++it) {
    
    (*it)->run(&res);

  }
  cout << res << endl;
  
  return 0;
}

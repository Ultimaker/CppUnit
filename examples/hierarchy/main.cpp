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

using namespace CppUnit;

BoardGameTest<BoardGame> bgt("BoardGameTest<BoardGame>");
ChessTest<Chess> ct("ChessTest<Chess>");


int 
main(int argc, char** argv)
{
  TextTestResult res;
  TestSuite suite;

  bgt.registerTests(&suite);
  ct.registerTests(&suite);

  vector<Test*> tests=TestRegistry::getRegistry().getAllTests();

  for(vector<Test*>::iterator it=tests.begin();
      it!=tests.end(); ++it) {
    
    (*it)->run(&res);

  }
  cout << res << endl;
  
  return 0;
}

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



int 
main(int argc, char** argv)
{
  CppUnit::TextTestResult res;
  CppUnit::TestSuite suite;

  BoardGameTest<BoardGame>* bgt = new BoardGameTest<BoardGame>("BoardGameTest<BoardGame>");
  ChessTest<Chess>* ct = new ChessTest<Chess>("ChessTest<Chess>");
  
  bgt->registerTests(&suite);
  ct->registerTests(&suite);

  std::vector<CppUnit::Test*> tests = 
      CppUnit::TestRegistry::getRegistry().getAllTests();

  for(std::vector<CppUnit::Test*>::iterator it=tests.begin();
      it!=tests.end(); ++it) {
    
    (*it)->run(&res);

  }
  std::cout << res << std::endl;

  delete ct;
  delete bgt;
  return 0;
}

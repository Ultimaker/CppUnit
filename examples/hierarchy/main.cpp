#include "cppunit/TextTestResult.h"
#include "cppunit/TestSuite.h"

#include "BoardGame.h"
#include "Chess.h"

#include "BoardGameTest.h"
#include "ChessTest.h"


#include <vector>
#include <iostream>



int 
main(int argc, char** argv)
{
  CppUnit::TestSuite suite;

  BoardGameTest<BoardGame> bgt("BoardGameTest<BoardGame>");
  ChessTest<Chess> ct("ChessTest<Chess>");
  
  bgt.registerTests(&suite);
  ct.registerTests(&suite);

  CppUnit::TextTestResult res;

  suite.run( &res );
  std::cout << res << std::endl;
  return 0;
}

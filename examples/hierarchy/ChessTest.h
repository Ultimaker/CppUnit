#ifndef __CHESSTEST_H__
#define __CHESSTEST_H__

#include "BoardGameTest.h"

template<class GAMECLASS> 
class ChessTest : public BoardGameTest<GAMECLASS> {
  public:
    ChessTest (string name) : BoardGameTest<GAMECLASS> (name) 
    {
    }
    
    ChessTest (TestSuite *suite) : BoardGameTest<GAMECLASS> (suite) 
    { 
      suite->addTest (
        new TestCaller<ChessTest> ("testNumberOfPieces", testNumberOfPieces));
    }
    
    void testNumberOfPieces () 
    { 
      assert (m_game->numberOfPieces () == 32); 
    }
};



#endif

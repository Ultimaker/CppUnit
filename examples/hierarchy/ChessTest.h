#ifndef __CHESSTEST_H__
#define __CHESSTEST_H__

#include "BoardGameTest.h"

template<typename GAMECLASS> 
class ChessTest : public BoardGameTest<GAMECLASS> {
  public:
    ChessTest (std::string name) : BoardGameTest<GAMECLASS> (name) 
    {
    }
    
    void registerTests(CppUnit::TestSuite *suite) 
    {
      BoardGameTest<GAMECLASS>::registerTests(suite);
      suite->addTest (
        new CppUnit::TestCaller<ChessTest<GAMECLASS> > ("testNumberOfPieces", 
          &ChessTest<GAMECLASS>::testNumberOfPieces, *this));
    }

    ChessTest() 
    {
    }
    
    void testNumberOfPieces () 
    { 
      assert (m_game->getNumberOfPieces () == 32); 
    }
};



#endif

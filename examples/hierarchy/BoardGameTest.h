#ifndef __BOARDGAMETEST_H__
#define __BOARDGAMETEST_H__

#include "TestCaller.h"

#ifndef CPPUNIT_TESTCASE_H
#include "TestCase.h"
#endif

template<class GAMECLASS> 
class BoardGameTest : public TestCase {
  protected:
    GAMECLASS	*m_game;
    
  public:
    BoardGameTest (string name) : TestCase (name) 
    {}
    
    BoardGameTest (TestSuite *suite) : TestCase ("") 
    { 
      suite->addTest (new TestCaller<BoardGameTest> ("testReset", testReset)); 
    }
    
    void setUp () 
    { m_game = new GAMECLASS; }
    
    void tearDown ()
    { delete m_game; }
    
    void testReset () 
    { assert (m_game->reset ()); }
    
};

#endif

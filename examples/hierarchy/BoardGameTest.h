#ifndef __BOARDGAMETEST_H__
#define __BOARDGAMETEST_H__

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

template<typename GAMECLASS> 
class BoardGameTest : public CppUnit::TestCase {
  protected:
    GAMECLASS	*m_game;
    
  public:
    BoardGameTest (std::string name) : CppUnit::TestCase (name) 
    {
    }

    virtual void registerTests(CppUnit::TestSuite *suite) 
    {
      suite->addTest (new CppUnit::TestCaller<BoardGameTest<GAMECLASS> > ("testReset", 
         &BoardGameTest<GAMECLASS>::testReset, *this)); 
      suite->addTest (new CppUnit::TestCaller<BoardGameTest<GAMECLASS> > ("testReset", 
         &BoardGameTest<GAMECLASS>::testResetShouldFail, *this)); 
    }

    BoardGameTest()
    {
    }

    int countTestCases () const
    { return 1; }
    
    void setUp () 
    { 
      m_game = new GAMECLASS; 
    }
    
    void tearDown ()
    { 
      delete m_game; 
    }
    
    void testReset () 
    { 
      assertImplementation (m_game->reset (),"m_game->reset ()",__LINE__,__FILE__); 
    }

    void testResetShouldFail () 
    { 
      std::cout << "The following test fails, this is intended:" << std::endl;
      assertImplementation (!m_game->reset (),"!m_game->reset ()",__LINE__,__FILE__); 
    }
    
};

#endif

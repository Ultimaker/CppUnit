#ifndef __BOARDGAMETEST_H__
#define __BOARDGAMETEST_H__

#include "cppunit/TestCaller.h"

#ifndef CPPUNIT_TESTCASE_H
#include "cppunit/TestCase.h"
#endif

#ifndef CPPUNIT_TESTSUITE_H
#include "cppunit/TestSuite.h"
#endif

#include <stdio.h>

template<class GAMECLASS> 
class BoardGameTest : public CppUnit::TestCase {
  protected:
    GAMECLASS	*m_game;
    
  public:
    BoardGameTest (string name) : CppUnit::TestCase (name) 
    {
    }
    
    BoardGameTest (CppUnit::TestSuite *suite) 
    { 
      suite->addTest (new CppUnit::TestCaller<BoardGameTest> ("testReset", testReset)); 
    }
    
    void runTest () 
    { 
      printf("runTest()\n");
      testReset();
      testResetShouldFail();
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
      printf("assertImpl()\n");
      assertImplementation (m_game->reset (),"m_game->reset ()",__LINE__,__FILE__); 
      printf("assertImpl() end\n");
    }

    void testResetShouldFail () 
    { 
      printf("!assertImpl()\n");
      assertImplementation (!m_game->reset (),"!m_game->reset ()",__LINE__,__FILE__); 
      printf("!assertImpl end()\n");
    }
    
};

#endif

#ifndef __BOARDGAMETEST_H__
#define __BOARDGAMETEST_H__

#include "cppunit/TestCaller.h"

#ifndef CPPUNIT_TESTCASE_H
#include "cppunit/TestCase.h"
#endif

#ifndef CPPUNIT_TESTSUITE_H
#include "cppunit/TestSuite.h"
#endif

template<class GAMECLASS> 
class BoardGameTest : public CppUnit::TestCase {
  protected:
    GAMECLASS	*m_game;
    
  public:
    BoardGameTest (string name) : CppUnit::TestCase (name) 
    {}
    
    BoardGameTest (CppUnit::TestSuite *suite) : CppUnit::TestCase ("") 
    { 
      suite->addTest (new CppUnit::TestCaller<BoardGameTest> ("testReset", testReset)); 
    }
    
    int countTestCases () const
    { return 1; }
    
    void setUp () 
    { m_game = new GAMECLASS; }
    
    void tearDown ()
    { delete m_game; }
    
    void testReset () 
    { assert (m_game->reset ()); }
    
};

#endif

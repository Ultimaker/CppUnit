// //////////////////////////////////////////////////////////////////////////
// Header file ClockerListener.h for class ClockerListener
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2002/04/19
// //////////////////////////////////////////////////////////////////////////
#ifndef CLOCKERLISTENER_H
#define CLOCKERLISTENER_H

#include <cppunit/TestListener.h>
#include <cppunit/TestPath.h>
#include <stack>
#include <vector>

#ifdef CLOCKER_USE_WINNTTIMER
#include "WinNtTimer.h"
typedef WinNtTimer Timer;
#else
#include "Timer.h"
#endif

/// TestListener that prints a flatten or hierarchical view of the test tree.
class ClockerListener : public CppUnit::TestListener
{
public:
  ClockerListener( bool flatten );

  virtual ~ClockerListener();

  void startTestRun( CppUnit::Test *test, 
                     CppUnit::TestResult *eventManager );

  void startTest( CppUnit::Test *test );

  void endTest( CppUnit::Test *test );

  void startSuite( CppUnit::Test *suite );

  void endSuite( CppUnit::Test *suite );

  void endTestRun( CppUnit::Test *test, 
                   CppUnit::TestResult *eventManager );

private:
  struct TestInfo
  {
    CppUnit::TestPath m_path;
    Timer m_timer;
    bool m_isSuite;
    std::vector<int> m_childIndexes;
  };

  void enterTest( CppUnit::Test *test,
                  bool isSuite );

  void exitTest( CppUnit::Test *test,
                 bool isSuite );

  void printStatistics() const;

  void printTest( const TestInfo &info,
                  const std::string &indentString ) const;

  void printTestIndent( const std::string &indent,
                        const int indentLength ) const;

  void printTestTime( double elapsedSeconds ) const;

  void printFlattenedTestName( const TestInfo &info ) const;

  void printTestName( const TestInfo &info ) const;

  /// Prevents the use of the copy constructor.
  ClockerListener( const ClockerListener &other );

  /// Prevents the use of the copy operator.
  void operator =( const ClockerListener &other );

private:
  bool m_flatten;
  CppUnit::TestPath m_currentPath;
  
  int m_testCount;
  double m_totalTestCaseTime;

  std::stack<int> m_testIndexes;
  std::vector<TestInfo> m_tests;
};



// Inlines methods for ClockerListener:
// -----------------------------------



#endif  // CLOCKERLISTENER_H

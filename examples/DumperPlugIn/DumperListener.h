// //////////////////////////////////////////////////////////////////////////
// Header file DumperListener.h for class DumperListener
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2002/04/19
// //////////////////////////////////////////////////////////////////////////
#ifndef DUMPERLISTENER_H
#define DUMPERLISTENER_H

#include <cppunit/TestListener.h>
#include <cppunit/TestPath.h>
#include <stack>


/// TestListener that prints a flatten or hierarchical view of the test tree.
class DumperListener : public CppUnit::TestListener
{
public:
  DumperListener( bool flatten );

  virtual ~DumperListener();

  void startTest( CppUnit::Test *test );

  void endTest( CppUnit::Test *test );

  void startSuite( CppUnit::Test *suite );

  void endSuite( CppUnit::Test *suite );

  void endTestRun( CppUnit::Test *test, 
                   CppUnit::TestResult *eventManager );

private:
  /// Prevents the use of the copy constructor.
  DumperListener( const DumperListener &other );

  /// Prevents the use of the copy operator.
  void operator =( const DumperListener &other );

  void printPath( CppUnit::Test *test, 
                  bool isSuite );

  void printFlattenedPath( bool isSuite );

  void printIndentedPathChild();

  std::string makeIndentString( int indentLevel );

private:
  bool m_flatten;
  CppUnit::TestPath m_path;
  
  int m_suiteCount;
  int m_testCount;
  int m_suiteWithTestCount;

  std::stack<bool> m_suiteHasTest;
};



// Inlines methods for DumperListener:
// -----------------------------------



#endif  // DUMPERLISTENER_H

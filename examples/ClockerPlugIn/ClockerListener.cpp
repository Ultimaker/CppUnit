// //////////////////////////////////////////////////////////////////////////
// Implementation file ClockerListener.cpp for class ClockerListener
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2002/04/19
// //////////////////////////////////////////////////////////////////////////
#include <cppunit/Test.h>
#include <iostream>
#include "ClockerListener.h"
#include <stdio.h>


ClockerListener::ClockerListener( bool flatten )
    : m_flatten( flatten )
    , m_testCount( 0 )
    , m_totalTestCaseTime( 0 )
{
}


ClockerListener::~ClockerListener()
{
}


void 
ClockerListener::startTestRun( CppUnit::Test *test, 
                               CppUnit::TestResult *eventManager )
{
  m_tests.reserve( test->countTestCases() *2 );
}


void 
ClockerListener::startTest( CppUnit::Test *test )
{
  enterTest( test, false );
  ++m_testCount;
}


void 
ClockerListener::endTest( CppUnit::Test *test )
{
  exitTest( test, false );
}


void 
ClockerListener::startSuite( CppUnit::Test *suite )
{
  enterTest( suite, true );
}


void 
ClockerListener::endSuite( CppUnit::Test *suite )
{
  exitTest( suite, true );
}


void 
ClockerListener::endTestRun( CppUnit::Test *test, 
                            CppUnit::TestResult *eventManager )
{
  printStatistics();
}


void 
ClockerListener::enterTest( CppUnit::Test *test,
                            bool isSuite )
{
  m_currentPath.add( test );

  int testIndex = m_tests.size();
  if ( !m_testIndexes.empty() )
    m_tests[ m_testIndexes.top() ].m_childIndexes.push_back( testIndex );
  m_testIndexes.push( testIndex );

  TestInfo info;
  info.m_timer.start();
  info.m_path = m_currentPath;
  info.m_isSuite = isSuite;

  m_tests.push_back( info );
}


void 
ClockerListener::exitTest( CppUnit::Test *test,
                           bool isSuite )
{
  m_tests[ m_testIndexes.top() ].m_timer.finish();
  if ( !isSuite )
    m_totalTestCaseTime += m_tests.back().m_timer.elapsedTime();

  m_currentPath.up();
  m_testIndexes.pop();
}


void 
ClockerListener::printStatistics() const
{
  printTest( m_tests[0], "" );
  std::cout  <<  std::endl;
  std::cout  <<  "Total elapsed time: ";
  printTestTime( m_tests[0].m_timer.elapsedTime() );
  std::cout  <<  ", average test case time: ";
  double average = 0;
  if ( m_testCount > 0 )
    average = m_totalTestCaseTime / m_testCount;
  printTestTime( average );
}


void 
ClockerListener::printTest( const TestInfo &info,
                            const std::string &indentString ) const
{
  std::string indent = indentString;
  const int indentLength = 3;

  if ( !m_flatten )
    printTestIndent( indentString, indentLength );

  printTestTime( info.m_timer.elapsedTime() );

  if ( m_flatten )
    printFlattenedTestName( info );
  else
    printTestName( info );

  std::cout  <<  std::endl;

  if ( info.m_childIndexes.empty() )
    indent+= std::string( indentLength, ' ' );
  else
    indent+= "|" + std::string( indentLength -1, ' ' );

  for ( int index =0; index < info.m_childIndexes.size(); ++index )
    printTest( m_tests[ info.m_childIndexes[ index ] ], indent );
}


void 
ClockerListener::printTestIndent( const std::string &indent,
                                  const int indentLength ) const
{
  if ( indent.empty() )
    return;

  std::cout << "   ";
  std::cout << indent.substr( 0, indent.length() - indentLength ) ;
  std::cout << "+"  <<  std::string( indentLength -1, '-' );
}


void 
ClockerListener::printTestTime( double elapsedSeconds ) const
{
  char buffer[320];
  const char *format;
  if ( elapsedSeconds < 1 )
    format = "(%2.3fs) ";
  else if ( elapsedSeconds < 10 )
    format = "(%3.2fs) ";
  else if (elapsedSeconds < 100 )
    format = "(%4.1fs) ";
  else
    format = "(%5fs) ";

  ::sprintf( buffer, format, elapsedSeconds );

  std::cout << buffer;
}


void 
ClockerListener::printFlattenedTestName( const TestInfo &info ) const
{
  std::cout  <<  info.m_path.toString();
  if ( info.m_isSuite )
    std::cout  <<  "/";
}


void 
ClockerListener::printTestName( const TestInfo &info ) const
{
  std::cout  <<  info.m_path.getChildTest()->getName();
}

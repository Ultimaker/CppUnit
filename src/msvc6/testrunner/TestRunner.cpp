// //////////////////////////////////////////////////////////////////////////
// Implementation file TestRunner.cpp for class TestRunner
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2001/04/26
// //////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include <msvc6/testrunner/TestRunner.h>
#include "TestRunnerModel.h"
#include "TestRunnerDlg.h"


TestRunner::TestRunner() :
    m_suite( new CppUnit::TestSuite() )
{
}


TestRunner::~TestRunner() 
{
  delete m_suite;

  for ( Tests::iterator it = m_tests.begin(); it != m_tests.end(); ++it )
    delete *it;
}


void 
TestRunner::run() 
{ 
  TestRunnerModel model( getRootTest() );
  TestRunnerDlg dlg( &model ); 
  dlg.DoModal (); 
}


void            
TestRunner::addTest(CppUnit::Test *test) 
{ 
  m_tests.push_back( test );
}


void            
TestRunner::addTests ( const std::vector<CppUnit::Test *> &tests ) 
{ 
  for ( std::vector<CppUnit::Test *>::const_iterator it=tests.begin();
        it != tests.end();
        ++it )
  {
    addTest( *it );
  }
}


CppUnit::Test *   
TestRunner::getRootTest()
{
  if ( m_tests.size() != 1 )
  {
    for ( Tests::iterator it = m_tests.begin(); it != m_tests.end(); ++it )
      m_suite->addTest( *it );
    m_tests.clear();
    return m_suite;
  }
  return m_tests[0];
}

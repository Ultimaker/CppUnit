// //////////////////////////////////////////////////////////////////////////
// Implementation file TestRunnerModel.cpp for class TestRunnerModel
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2001/04/26
// //////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TestRunnerModel.h"
#include <algorithm>
#include <cppunit/testsuite.h>


TestRunnerModel::TestRunnerModel( CppUnit::Test *rootTest ) :
    m_rootTest( rootTest )
{
}


TestRunnerModel::~TestRunnerModel()
{
}

const TestRunnerModel::History &
TestRunnerModel::history() const
{
  return m_history;
}


void 
TestRunnerModel::selectHistoryTest( CppUnit::Test *test )
{
  History::iterator end = 
      std::remove( m_history.begin(), m_history.end(), test );
  m_history.erase( end, m_history.end() );
  
  if ( test != NULL )
    m_history.push_front( test );
}


CppUnit::Test *
TestRunnerModel::selectedTest() const
{
  if ( m_history.size() > 0 )
    return m_history[0];
  return NULL;
}


void 
TestRunnerModel::loadSettings(Settings & s)
{
  CWinApp *app = AfxGetApp();
  ASSERT( app != NULL );

  int autorun = app->GetProfileInt( "CppUnit", 
                                    "AutorunAtStartup",
                                    1 );
  s.autorunOnLaunch = (autorun == 1);

  s.dlgBounds.left = app->GetProfileInt( "CppUnit", "Left", 0 );
  s.dlgBounds.top = app->GetProfileInt( "CppUnit", "Top", 0 );
  s.dlgBounds.right = app->GetProfileInt( "CppUnit", "Right", 0 );
  s.dlgBounds.bottom= app->GetProfileInt( "CppUnit", "Bottom", 0 );  

  s.col_1 = app->GetProfileInt( "CppUnit", "Col_1", 40 );
  s.col_2 = app->GetProfileInt( "CppUnit", "Col_2", 40 );
  s.col_3 = app->GetProfileInt( "CppUnit", "Col_3", 40 );
  s.col_4 = app->GetProfileInt( "CppUnit", "Col_4", 40 );

  loadHistory();
}


void 
TestRunnerModel::loadHistory()
{
  m_history.clear();
  int idx = 1;
  do
  {
    std::string testName = loadHistoryEntry( idx++ );
    if ( testName.empty() )
      break;

    CppUnit::Test *test = findTestByName( testName );
    if ( test != NULL )
      m_history.push_back( test );
  }
  while ( true );
}


std::string 
TestRunnerModel::loadHistoryEntry( int idx )
{
  CWinApp *app = AfxGetApp();
  ASSERT( app != NULL );

  return std::string( 
      app->GetProfileString( "CppUnit", 
                             getHistoryEntryName( idx ).c_str() ) );
}


void 
TestRunnerModel::saveSettings( const Settings & s )
{
  CWinApp *app = AfxGetApp();
  ASSERT( app != NULL );

  int autorun = s.autorunOnLaunch ? 1 : 0;
  app->WriteProfileInt( "CppUnit", "AutorunAtStartup", autorun );

  app->WriteProfileInt( "CppUnit", "Left",	 s.dlgBounds.left );
  app->WriteProfileInt( "CppUnit", "Top",	 s.dlgBounds.top );
  app->WriteProfileInt( "CppUnit", "Right",  s.dlgBounds.right );
  app->WriteProfileInt( "CppUnit", "Bottom", s.dlgBounds.bottom );

  app->WriteProfileInt( "CppUnit", "Col_1",	 s.col_1 );
  app->WriteProfileInt( "CppUnit", "Col_2",	 s.col_2 );
  app->WriteProfileInt( "CppUnit", "Col_3",	 s.col_3 );
  app->WriteProfileInt( "CppUnit", "Col_4",	 s.col_4 );

  int idx = 1;
  for ( History::const_iterator it = m_history.begin(); 
        it != m_history.end(); 
        ++it , ++idx )
  {
    CppUnit::Test *test = *it;
    saveHistoryEntry( idx, test->getName() );
  }
}


void 
TestRunnerModel::saveHistoryEntry( int idx, 
                                   std::string testName )
{
  CWinApp *app = AfxGetApp();
  ASSERT( app != NULL );

  app->WriteProfileString( "CppUnit", 
                           getHistoryEntryName( idx ).c_str(), 
                           testName.c_str() );
}


std::string 
TestRunnerModel::getHistoryEntryName( int idx ) const
{
  char entry[20];
  ::sprintf( entry, "HistoryTest%d", idx );
  return std::string( entry );
}


CppUnit::Test *
TestRunnerModel::rootTest()
{
  return m_rootTest;
}


void 
TestRunnerModel::setRootTest( CppUnit::Test *test )
{
  m_rootTest = test;
}


CppUnit::Test * 
TestRunnerModel::findTestByName( std::string name ) const
{
  return findTestByNameFor( name, m_rootTest );
}


CppUnit::Test * 
TestRunnerModel::findTestByNameFor( const std::string &name, 
                                    CppUnit::Test *test ) const
{
  if ( name == test->getName() )
    return test;

  CppUnit::TestSuite *suite = dynamic_cast<CppUnit::TestSuite *>(test);
  if ( suite == NULL )
    return NULL;

  const std::vector<CppUnit::Test *> &tests = suite->getTests();
  for ( std::vector<CppUnit::Test *>::const_iterator it = tests.begin(); 
        it != tests.end(); 
        ++it )
  {
    CppUnit::Test *testFound = findTestByNameFor( name, *it );
    if ( testFound != NULL )
      return testFound;
  }
  return NULL;
}

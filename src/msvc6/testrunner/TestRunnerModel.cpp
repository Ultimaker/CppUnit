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
    m_autorunOnLaunch( true ),
    m_rootTest( rootTest )
{
}


TestRunnerModel::~TestRunnerModel()
{
}


bool 
TestRunnerModel::autorunOnLaunch() const
{
  return m_autorunOnLaunch;
}


void 
TestRunnerModel::setAutorunOnLaunch( bool autorunOnLaunch )
{
  m_autorunOnLaunch = autorunOnLaunch;
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
TestRunnerModel::loadSettings()
{
  CWinApp *app = AfxGetApp();
  ASSERT( app != NULL );

  int autorun = app->GetProfileInt( "CppUnit", 
                                    "AutorunAtStartup",
                                    1 );
  m_autorunOnLaunch = (autorun == 1);


  m_history.clear();
  int idx = 1;
  do
  {
    std::string testName = loadHistoryEntry( idx++ );
    if ( testName.empty() )
      break;

    CppUnit::Test *test = findTestByName( testName );
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
TestRunnerModel::saveSettings()
{
  CWinApp *app = AfxGetApp();
  ASSERT( app != NULL );

  int autorun = m_autorunOnLaunch ? 1 : 0;
  app->WriteProfileInt( "CppUnit", "AutorunAtStartup", autorun );

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

  std::vector<CppUnit::Test *> tests& = suite->getTests();
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

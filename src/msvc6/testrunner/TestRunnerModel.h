// //////////////////////////////////////////////////////////////////////////
// Header file TestRunnerModel.h for class TestRunnerModel
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2001/04/26
// //////////////////////////////////////////////////////////////////////////
#ifndef TESTRUNNERMODEL_H
#define TESTRUNNERMODEL_H

#include <deque>
#include <cppunit/Test.h>


/*! \class TestRunnerModel
 * \brief This class represents a model for the test runner.
 */
class AFX_CLASS_EXPORT TestRunnerModel
{
public:
  typedef std::deque<CppUnit::Test *> History;

  /*! Constructs a TestRunnerModel object.
   */
  TestRunnerModel( CppUnit::Test *rootTest );

  /*! Destructor.
   */
  virtual ~TestRunnerModel();

  virtual void setRootTest( CppUnit::Test *rootTest );

  void loadSettings();
  void saveSettings();

  bool autorunOnLaunch() const;
  void setAutorunOnLaunch( bool autorunOnLaunch );

  const History &history() const;
  void selectHistoryTest( CppUnit::Test *test );
  CppUnit::Test *selectedTest() const;

  CppUnit::Test *rootTest();

protected:
  void loadHistory();
  std::string loadHistoryEntry( int idx );
  CppUnit::Test *findTestByName( std::string name ) const;
  CppUnit::Test *findTestByNameFor( const std::string &name, 
                                    CppUnit::Test *test ) const;

  void saveHistoryEntry( int idx, 
                         std::string testName );

  std::string getHistoryEntryName( int idx ) const;

private:
  /// Prevents the use of the copy constructor.
  TestRunnerModel( const TestRunnerModel &copy );

  /// Prevents the use of the copy operator.
  TestRunnerModel &operator =( const TestRunnerModel &copy );

private:
  bool m_autorunOnLaunch;
  
  History m_history;

  CppUnit::Test *m_rootTest;
};



// Inlines methods for TestRunnerModel:
// ------------------------------------



#endif  // TESTRUNNERMODEL_H

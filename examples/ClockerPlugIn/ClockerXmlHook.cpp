// //////////////////////////////////////////////////////////////////////////
// Implementation file ClockerXmlHook.cpp for class ClockerXmlHook
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2002/06/14
// //////////////////////////////////////////////////////////////////////////

#include <cppunit/Test.h>
#include <cppunit/tools/XmlElement.h>
#include "ClockerModel.h"
#include "ClockerXmlHook.h"


ClockerXmlHook::ClockerXmlHook( ClockerModel *model )
    : m_model( model )
{
}


ClockerXmlHook::~ClockerXmlHook()
{
}


void 
ClockerXmlHook::endDocument( CppUnit::XmlDocument *document,
                             CppUnit::XmlElement *rootNode )
{
  CppUnit::XmlElement *testTreeElement = new CppUnit::XmlElement( "TimedTestTree" );
  rootNode->addElement( testTreeElement );

  addTimedTest( testTreeElement, 0 );
}


void 
ClockerXmlHook::addTimedTest( CppUnit::XmlElement *parentElement, 
                              int testIndex )
{
  std::string elementName = m_model->isSuite( testIndex ) ? "TimedSuite" : "TimedTest";
  CppUnit::XmlElement *testElement = new CppUnit::XmlElement( elementName );
  parentElement->addElement( testElement );
  testElement->addAttribute( "id", testIndex );

  const CppUnit::TestPath &path = m_model->testPathFor( testIndex );
  testElement->addElement( new CppUnit::XmlElement( "Name", 
                                                    path.getChildTest()->getName() ) );
  testElement->addElement( new CppUnit::XmlElement( "TestPath", path.toString() ) );
  testElement->addElement( new CppUnit::XmlElement( "Time", 
                                 ClockerModel::timeStringFor( 
                                    m_model->testTimeFor( testIndex ) ) ) );

  if ( m_model->isSuite( testIndex ) )
  {
    for ( int childIndex =0; childIndex < m_model->childCountFor( testIndex ); ++childIndex )
      addTimedTest( testElement, m_model->childAtFor( testIndex, childIndex ) );
  }
}


void 
ClockerXmlHook::failTestAdded( CppUnit::XmlDocument *document,
                               CppUnit::XmlElement *testNode,
                               CppUnit::Test *test,
                               CppUnit::TestFailure *failure )
{
  successfulTestAdded( document, testNode, test );
}


void 
ClockerXmlHook::successfulTestAdded( CppUnit::XmlDocument *document,
                                     CppUnit::XmlElement *testNode,
                                     CppUnit::Test *test )
{
  int testIndex = m_model->indexOf( test );
  double time = (testIndex >= 0) ? m_model->testTimeFor( testIndex ) : 0.0;
  const CppUnit::TestPath &path = m_model->testPathFor( testIndex );
  testNode->addElement( new CppUnit::XmlElement( "TestPath", path.toString() ) );
  testNode->addElement( new CppUnit::XmlElement( "Time",
                               ClockerModel::timeStringFor( time ) ) );
}


void 
ClockerXmlHook::statisticsAdded( CppUnit::XmlDocument *document,
                                 CppUnit::XmlElement *statisticsNode )
{
  statisticsNode->addElement( 
      new CppUnit::XmlElement( "TotalElapsedTime",
           ClockerModel::timeStringFor( m_model->totalElapsedTime() ) ) );
  statisticsNode->addElement( 
      new CppUnit::XmlElement( "AverageTestCaseTime",
           ClockerModel::timeStringFor( m_model->averageTestCaseTime() ) ) );
}

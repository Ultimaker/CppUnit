// //////////////////////////////////////////////////////////////////////////
// Header file ClockerXmlHook.h for class ClockerXmlHook
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2002/06/14
// //////////////////////////////////////////////////////////////////////////
#ifndef CLOCKERXMLHOOK_H
#define CLOCKERXMLHOOK_H

#include <cppunit/XmlOutputterHook.h>

class ClockerModel;



/// XML output hook to add test timing and test hierarchy timing.
class ClockerXmlHook : public CppUnit::XmlOutputterHook
{
public:
  /*! Constructs a ClockerXmlHook object.
   */
  ClockerXmlHook( ClockerModel *model );

  /// Destructor.
  virtual ~ClockerXmlHook();

  void endDocument( CppUnit::XmlDocument *document,
                    CppUnit::XmlElement *rootNode );

  void failTestAdded( CppUnit::XmlDocument *document,
                      CppUnit::XmlElement *testNode,
                      CppUnit::Test *test,
                      CppUnit::TestFailure *failure );

  void successfulTestAdded( CppUnit::XmlDocument *document,
                            CppUnit::XmlElement *testNode,
                            CppUnit::Test *test );

  void statisticsAdded( CppUnit::XmlDocument *document,
                        CppUnit::XmlElement *statisticsNode );

private:
  /// Prevents the use of the copy constructor.
  ClockerXmlHook( const ClockerXmlHook &other );

  /// Prevents the use of the copy operator.
  void operator =( const ClockerXmlHook &other );

  void addTimedTest( CppUnit::XmlElement *parentElement, 
                     int testIndex );

private:
  ClockerModel *m_model;
};



// Inlines methods for ClockerXmlHook:
// -----------------------------------



#endif  // CLOCKERXMLHOOK_H

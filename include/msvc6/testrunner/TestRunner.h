// //////////////////////////////////////////////////////////////////////////
// Header file TestRunner.h for class TestRunner
// (c)Copyright 2000, Baptiste Lepilleur.
// Created: 2001/04/26
// //////////////////////////////////////////////////////////////////////////
#ifndef TESTRUNNER_TESTRUNNER_H
#define TESTRUNNER_TESTRUNNER_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vector>
#include <cppunit/TestSuite.h>


// A Wrapper
class AFX_CLASS_EXPORT TestRunner 
{
public:
         TestRunner ();
         ~TestRunner ();

    void run ();

    void addTest (CppUnit::Test *test);

    void addTests (const std::vector<CppUnit::Test *> &tests); 

protected:
  CppUnit::Test *   getRootTest();

  CppUnit::TestSuite *m_suite;

  typedef std::vector<CppUnit::Test *> Tests;
  Tests m_tests;
};

#endif  // TESTRUNNER_TESTRUNNER_H

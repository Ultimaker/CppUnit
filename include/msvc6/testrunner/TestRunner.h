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

/* Refer to MSDN documentation to know how to write and use MFC extension DLL:
   mk:@MSITStore:h:\DevStudio\MSDN\98VSa\1036\vcmfc.chm::/html/_mfcnotes_tn033.htm#_mfcnotes_how_to_write_an_mfc_extension_dll
   
   This can be found in the index with "mfc extension"
   The basic:
   Using:
   - your application must use MFC DLL
   - memory allocation is done using the same heap
   - you must define the symbol _AFX_DLL

   Building:
   - you must define the symbol _AFX_DLL and _AFX_EXT
   - export class using AFX_EXT_CLASS
 */



// A Wrapper
class AFX_EXT_CLASS TestRunner 
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

#if !defined(AFX_TESTRUNNERDLG_H)
#define AFX_TESTRUNNERDLG_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestRunnerDlg.h : header file
//

#include <vector>

#ifndef CPPUNIT_TEST_H
#include <cppunit/Test.h>
#endif

#ifndef CPPUNIT_EXCEPTION_H
#include <cppunit/Exception.h>
#endif


class ProgressBar;
class ActiveTest;


/////////////////////////////////////////////////////////////////////////////
// TestRunnerDlg dialog

class AFX_CLASS_EXPORT TestRunnerDlg : public CDialog
{
// Construction
public:
                    TestRunnerDlg       (CWnd* pParent = NULL);
                    ~TestRunnerDlg      ();

    void            setTests            (std::vector<CppUnit::Test *> *test);

    void            addError            (CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e);
    void            addFailure          (CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e);
    void            endTest             (CppUnit::TestResult *result, CppUnit::Test *test);

// Dialog Data
    //{{AFX_DATA(TestRunnerDlg)
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(TestRunnerDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(TestRunnerDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnRun();
    afx_msg void OnStop();
    virtual void OnOK();
    afx_msg void OnSelchangeComboTest();
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    ProgressBar                   *m_testsProgress;
    std::vector<CppUnit::Test *>  *m_tests;
    CppUnit::Test                 *m_selectedTest;
    ActiveTest                    *m_activeTest;
    CppUnit::TestResult           *m_result;
    int                           m_testsRun;
    int                           m_errors;
    int                           m_failures;
    DWORD                         m_testStartTime;
    DWORD                         m_testEndTime;

    void            addListEntry        (std::string type, CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e);
    void            beIdle              ();
    void            beRunning           ();
    void            beRunDisabled       ();
    void            reset               ();
    void            freeState           ();
    void            updateCountsDisplay ();

};


inline void TestRunnerDlg::setTests (std::vector<CppUnit::Test *> *tests)
{ m_tests = tests; }




/////////////////////////////////////////////////////////////////////////////
// A Wrapper


class AFX_CLASS_EXPORT TestRunner 
{
    std::vector<CppUnit::Test *>  m_tests;

public:
                    TestRunner () {}
                    ~TestRunner () 
                    {
                        for (std::vector<CppUnit::Test *>::iterator it = m_tests.begin (); it != m_tests.end (); ++it)
                            delete *it;
                    }

    void            run () 
                    { 
                        TestRunnerDlg dlg; 

                        dlg.setTests (&m_tests);
                        dlg.DoModal (); 
                    }

    void            addTest (CppUnit::Test *test) 
                    { m_tests.push_back (test); }


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRUNNERDLG_H)

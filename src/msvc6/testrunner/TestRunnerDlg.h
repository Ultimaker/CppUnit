#if !defined(AFX_TESTRUNNERDLG_H)
#define AFX_TESTRUNNERDLG_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestRunnerDlg.h : header file
//

#include <vector>
#include <cppunit/TestSuite.h>
#include <cppunit/Exception.h>

#include "ActiveTest.h"

class ProgressBar;
class TestRunnerModel;


/////////////////////////////////////////////////////////////////////////////
// TestRunnerDlg dialog

class TestRunnerDlg : public CDialog
{
// Construction
public:
                    TestRunnerDlg       ( TestRunnerModel *model,
                                          CWnd* pParent = NULL);
                    ~TestRunnerDlg      ();

    void            addError            (CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e);
    void            addFailure          (CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e);
    void            endTest             (CppUnit::TestResult *result, CppUnit::Test *test);

// Dialog Data
    //{{AFX_DATA(TestRunnerDlg)
	CButton	m_buttonClose;
	CButton	m_buttonStop;
	CButton	m_buttonRun;
	BOOL	m_bAutorunAtStartup;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(TestRunnerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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
	afx_msg void OnBrowseTest();
	afx_msg void OnQuitApplication();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    typedef std::vector<CppUnit::Test *> Tests;
    ProgressBar     *m_testsProgress;
    CppUnit::Test            *m_selectedTest;
    ActiveTest      *m_activeTest;
    CppUnit::TestResult      *m_result;
    int             m_testsRun;
    int             m_errors;
    int             m_failures;
    DWORD           m_testStartTime;
    DWORD           m_testEndTime;
    static const CString ms_cppunitKey;
    HACCEL          m_hAccelerator;
    bool            m_bIsRunning;
    TestRunnerModel *m_model;

    void            addListEntry        (std::string type, CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e);
    void            beIdle              ();
    void            beRunning           ();
    void            beRunDisabled       ();
    void            reset               ();
    void            freeState           ();
    void            updateCountsDisplay ();
    void            setupHistoryCombo   ();
    CppUnit::Test * findTestByName( std::string name ) const;
    CppUnit::Test * findTestByNameFor( const std::string &name, CppUnit::Test *test ) const;
    void            addNewTestToHistory( CppUnit::Test *test );
    void            addTestToHistoryCombo( CppUnit::Test *test, int idx =-1 );
    void            removeTestFromHistory( CppUnit::Test *test );
    CComboBox *     getHistoryCombo();
    void            updateSelectedItem();
    void            saveHistory();
    void            loadSettings();
    void            saveSettings();
    TestRunnerModel &model();
    void updateHistoryCombo();
};




//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRUNNERDLG_H)

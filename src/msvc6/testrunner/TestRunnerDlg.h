#if !defined(AFX_TESTRUNNERDLG_H)
#define AFX_TESTRUNNERDLG_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestRunnerDlg.h : header file
//

/* Refer to MSDN documentation:
   mk:@MSITStore:h:\DevStudio\MSDN\98VSa\1036\vcmfc.chm::/html/_mfcnotes_tn033.htm#_mfcnotes_how_to_write_an_mfc_extension_dll
   to know how to write and use MFC extension DLL
   Can be found in the index with "mfc extension"
   =>
   Using:
   - your application must link  Multithreaded MFC DLL
   - memory allocation is done using the same heap
   - you must define the symbol _AFX_DLL
   Building:
   - you must define the symbol _AFX_DLL and _AFX_EXT
 */


#include <vector>
#include <cppunit/TestSuite.h>
#include <cppunit/Exception.h>

#include "ActiveTest.h"

class ProgressBar;
class TestRunnerModel;


/////////////////////////////////////////////////////////////////////////////
// TestRunnerDlg dialog

class AFX_EXT_CLASS TestRunnerDlg : public CDialog
{
public:
  TestRunnerDlg( TestRunnerModel *model,
                int nDialogResourceId = -1,
                CWnd* pParent = NULL);
  ~TestRunnerDlg();

  void addError( CppUnit::TestResult *result, 
                 CppUnit::Test *test, 
                 CppUnit::Exception *e );
  void addFailure( CppUnit::TestResult *result, 
                   CppUnit::Test *test, 
                   CppUnit::Exception *e );
  void endTest( CppUnit::TestResult *result, 
                CppUnit::Test *test );

  //{{AFX_DATA(TestRunnerDlg)
  CButton	m_buttonClose;
  CButton	m_buttonStop;
  CButton	m_buttonRun;
  BOOL	m_bAutorunAtStartup;
  //}}AFX_DATA

  //{{AFX_VIRTUAL(TestRunnerDlg)
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

protected:

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
  ProgressBar *m_testsProgress;
  CppUnit::Test *m_selectedTest;
  ActiveTest *m_activeTest;
  CppUnit::TestResult *m_result;
  int m_testsRun;
  int m_errors;
  int m_failures;
  DWORD m_testStartTime;
  DWORD m_testEndTime;
  static const CString ms_cppunitKey;
  HACCEL m_hAccelerator;
  bool m_bIsRunning;
  TestRunnerModel *m_model;
  CImageList m_errorListBitmap;

  enum ErrorTypeBitmaps
  {
    errorTypeFailure =0,
    errorTypeError
  };

  void addListEntry( std::string type, 
                     CppUnit::TestResult *result, 
                     CppUnit::Test *test, 
                     CppUnit::Exception *e );
  void beIdle();
  void beRunning();
  void beRunDisabled();
  void reset();
  void freeState();
  void updateCountsDisplay();
  void setupHistoryCombo();
  CppUnit::Test *findTestByName( std::string name ) const;
  CppUnit::Test *findTestByNameFor( const std::string &name, 
                                    CppUnit::Test *test ) const;
  void addNewTestToHistory( CppUnit::Test *test );
  void addTestToHistoryCombo( CppUnit::Test *test, 
                              int idx =-1 );
  void removeTestFromHistory( CppUnit::Test *test );
  CComboBox *getHistoryCombo();
  void updateSelectedItem();
  void saveHistory();
  void loadSettings();
  void saveSettings();
  TestRunnerModel &model();
  void updateHistoryCombo();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRUNNERDLG_H)

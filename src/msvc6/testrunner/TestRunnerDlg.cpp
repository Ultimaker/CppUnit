// TestRunnerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mmsystem.h"
#include "TestRunnerApp.h"
#include "TestRunnerDlg.h"
#include "Resource.h"
#include "ActiveTest.h"
#include "GUITestResult.h"
#include "ProgressBar.h"
#include "TreeHierarchyDlg.h"
#include "TestRunnerModel.h"
#include "ListCtrlFormatter.h"
#include "ListCtrlSetter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* TODO:
 - rewrite history management. It's quite messy.
   => don't store test as data, use a vector a most recently used test instead.
 */


/////////////////////////////////////////////////////////////////////////////
// TestRunnerDlg dialog

const CString TestRunnerDlg::ms_cppunitKey( "CppUnit" );


TestRunnerDlg::TestRunnerDlg( TestRunnerModel *model,
                              int nDialogResourceId,
                              CWnd* pParent ) :
    CDialog( nDialogResourceId == -1 ? IDD_DIALOG_TESTRUNNER :
                                       nDialogResourceId, 
             pParent),
    m_model( model )
{
    //{{AFX_DATA_INIT(TestRunnerDlg)
	m_bAutorunAtStartup = FALSE;
	//}}AFX_DATA_INIT

    m_testsProgress     = 0;
    m_selectedTest      = 0;
    m_bAutorunAtStartup = true;
    m_bIsRunning = false;
}


void TestRunnerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(TestRunnerDlg)
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
	DDX_Control(pDX, IDOK, m_buttonClose);
	DDX_Control(pDX, ID_STOP, m_buttonStop);
	DDX_Control(pDX, ID_RUN, m_buttonRun);
	DDX_Check(pDX, IDC_CHECK_AUTORUN, m_bAutorunAtStartup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TestRunnerDlg, CDialog)
  //{{AFX_MSG_MAP(TestRunnerDlg)
  ON_BN_CLICKED(ID_RUN, OnRun)
  ON_BN_CLICKED(ID_STOP, OnStop)
  ON_CBN_SELCHANGE(IDC_COMBO_TEST, OnSelchangeComboTest)
  ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BROWSE_TEST, OnBrowseTest)
	ON_COMMAND(ID_QUIT_APPLICATION, OnQuitApplication)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TestRunnerDlg message handlers

BOOL TestRunnerDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

//    m_hAccelerator = ::LoadAccelerators( AfxGetResourceHandle(),
    m_hAccelerator = ::LoadAccelerators( g_testRunnerResource,
                                         MAKEINTRESOURCE( IDR_ACCELERATOR_TEST_RUNNER ) );
// It always fails!!! I don't understand why. Complain about not finding the resource name!
    ASSERT( m_hAccelerator !=NULL );
    
    CListCtrl   *listCtrl = (CListCtrl *)GetDlgItem (IDC_LIST);
    CComboBox   *comboBox = (CComboBox *)GetDlgItem (IDC_COMBO_TEST);

    ASSERT (listCtrl);
    ASSERT (comboBox);
    ListCtrlFormatter formatter( *listCtrl );

    VERIFY( m_errorListBitmap.Create( IDB_ERROR_TYPE, 16, 1, 
                                      RGB( 255,0,255 ) ) );

    listCtrl->SetImageList( &m_errorListBitmap, LVSIL_SMALL );

    int averageCharWidth = listCtrl->GetStringWidth("#");
    formatter.AddColumn( IDS_ERRORLIST_TYPE, 4*averageCharWidth, LVCFMT_LEFT, 0 );
    formatter.AddColumn( IDS_ERRORLIST_NAME, 32*averageCharWidth, LVCFMT_LEFT, 1 );
    formatter.AddColumn( IDS_ERRORLIST_FAILED_CONDITION, 20*averageCharWidth, LVCFMT_LEFT, 2 );
    formatter.AddColumn( IDS_ERRORLIST_LINE_NUMBER, 5*averageCharWidth, LVCFMT_LEFT, 3 );
    formatter.AddColumn( IDS_ERRORLIST_FILE_NAME, 10*averageCharWidth, LVCFMT_LEFT, 4 );


    m_testsProgress = new ProgressBar (this, CRect (50, 85, 50 + 425, 85 + 25));

    reset ();

    loadSettings();
    updateHistoryCombo();

    UpdateData( FALSE );

    // somehow doesn't have the desired effect?
    LONG extendedStyle = GetWindowLong( m_listCtrl.GetSafeHwnd(), 
                                        GWL_EXSTYLE);;
    SetWindowLong( m_listCtrl.GetSafeHwnd(), 
                   GWL_EXSTYLE, 
                   extendedStyle | LVS_EX_FULLROWSELECT);

    m_buttonRun.SetFocus();

    if ( m_bAutorunAtStartup )
      OnRun();
    
    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

TestRunnerDlg::~TestRunnerDlg ()
{ 
  saveSettings();
  freeState ();
  delete m_testsProgress;
}

void TestRunnerDlg::OnRun() 
{
  if ( m_bIsRunning )
    return;

  m_selectedTest = m_model->selectedTest();

  if (m_selectedTest == 0)
	  return;

  freeState       (); 
  reset           ();

  beRunning       ();

  int numberOfTests = m_selectedTest->countTestCases ();

  m_testsProgress->start (numberOfTests);

  m_result            = new GUITestResult ((TestRunnerDlg *)this);
  m_activeTest        = new ActiveTest (m_selectedTest);

  m_testStartTime     = timeGetTime ();

  m_activeTest->run (m_result);

  m_testEndTime       = timeGetTime ();
}


void TestRunnerDlg::addListEntry (std::string type, CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e)
{
//    char        stage [80];
//    LV_ITEM     lvi;
    CListCtrl   *listCtrl       = (CListCtrl *)GetDlgItem (IDC_LIST);
    int         currentEntry    = result->testErrors () + result->testFailures ()-1;

    ErrorTypeBitmaps errorType;
    if ( type == "Failure" )
      errorType = errorTypeFailure;
    else
      errorType = errorTypeError;

    ListCtrlSetter setter( *listCtrl );
    setter.insertLine( currentEntry );
    setter.addSubItem( errorType, type );

    // Set test name
    setter.addSubItem( errorType, test->getName() );

    // Set the asserted text
    setter.addSubItem( e->what() );

    // Set the line number
    if (e->lineNumber () == CppUnit::Exception::UNKNOWNLINENUMBER)
      setter.addSubItem( "?" );
    else
    {
      char tmp[64];
      sprintf( tmp, "%ld", e->lineNumber() );
      setter.addSubItem( tmp );
    }

    // Set the file name
    setter.addSubItem( e->fileName() );

/*
    sprintf (stage, "%s", type.c_str ());

    lvi.mask        = LVIF_TEXT;
    lvi.iItem       = currentEntry;
    lvi.iSubItem    = 0;
    lvi.pszText     = stage;
    lvi.iImage      = 0;
    lvi.stateMask   = 0;
    lvi.state       = 0;

    listCtrl->InsertItem (&lvi);

    // Set class string
    listCtrl->SetItemText (currentEntry, 1, test->getName ().c_str ());

    // Set the asserted text
    listCtrl->SetItemText(currentEntry, 2, e->what ());

    // Set the line number
    if (e->lineNumber () == CppUnit::Exception::UNKNOWNLINENUMBER)
        sprintf (stage, "<unknown>");
    else
        sprintf (stage, "%ld", e->lineNumber ());

    listCtrl->SetItemText(currentEntry, 3, stage);

    // Set the file name
    listCtrl->SetItemText(currentEntry, 4, e->fileName ().c_str ());
*/
    listCtrl->RedrawItems (currentEntry, currentEntry);
    listCtrl->UpdateWindow ();

}



void TestRunnerDlg::addError (CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e)
{
    addListEntry ("Error", result, test, e);
    m_errors++;

    updateCountsDisplay ();

}

void TestRunnerDlg::addFailure (CppUnit::TestResult *result, CppUnit::Test *test, CppUnit::Exception *e)
{
    addListEntry ("Failure", result, test, e);
    m_failures++;

    updateCountsDisplay ();

}


void TestRunnerDlg::endTest (CppUnit::TestResult *result, CppUnit::Test *test)
{
	if (m_selectedTest == 0)
		return;

    m_testsRun++;
    updateCountsDisplay ();
    m_testsProgress->step (m_failures == 0 && m_errors == 0);

    m_testEndTime   = timeGetTime ();

    updateCountsDisplay ();

    if (m_testsRun >= m_selectedTest->countTestCases ())
        beIdle ();
}


void TestRunnerDlg::beRunning ()
{
    m_bIsRunning = true;
    m_buttonRun.EnableWindow( FALSE );
    m_buttonClose.EnableWindow( FALSE );

//    m_buttonRun.SetButtonStyle( m_buttonRun.GetButtonStyle() & ~BS_DEFPUSHBUTTON );
//    m_buttonStop.SetButtonStyle( m_buttonStop.GetButtonStyle() | BS_DEFPUSHBUTTON );
}


void TestRunnerDlg::beIdle ()
{
    m_bIsRunning = false;
    m_buttonRun.EnableWindow( TRUE );
    m_buttonClose.EnableWindow( TRUE );

    m_buttonRun.SetButtonStyle( m_buttonRun.GetButtonStyle() | BS_DEFPUSHBUTTON );
//    m_buttonStop.SetButtonStyle( m_buttonStop.GetButtonStyle() & ~BS_DEFPUSHBUTTON );
}

void TestRunnerDlg::beRunDisabled ()
{
    m_bIsRunning = false;
    m_buttonRun.EnableWindow( FALSE );
    m_buttonStop.EnableWindow( FALSE );
    m_buttonClose.EnableWindow( TRUE );

//    m_buttonRun.SetButtonStyle( m_buttonRun.GetButtonStyle() | BS_DEFPUSHBUTTON );
//    m_buttonStop.SetButtonStyle( m_buttonStop.GetButtonStyle() & ~BS_DEFPUSHBUTTON );
}


void TestRunnerDlg::freeState ()
{
    delete m_activeTest;
    delete m_result;

}

void TestRunnerDlg::reset ()
{
    m_testsRun      = 0;
    m_errors        = 0;
    m_failures      = 0;
    m_testEndTime   = m_testStartTime;

    updateCountsDisplay ();

    m_activeTest    = 0;
    m_result        = 0;

    CListCtrl *listCtrl = (CListCtrl *)GetDlgItem (IDC_LIST);

    listCtrl->DeleteAllItems ();
    m_testsProgress->reset ();

}


void TestRunnerDlg::updateCountsDisplay ()
{
    CStatic *statTestsRun   = (CStatic *)GetDlgItem (IDC_STATIC_RUNS);
    CStatic *statErrors     = (CStatic *)GetDlgItem (IDC_STATIC_ERRORS);
    CStatic *statFailures   = (CStatic *)GetDlgItem (IDC_STATIC_FAILURES);
    CEdit *editTime         = (CEdit *)GetDlgItem (IDC_EDIT_TIME);

    CString argumentString;

    argumentString.Format ("%d", m_testsRun);
    statTestsRun    ->SetWindowText (argumentString);

    argumentString.Format ("%d", m_errors);
    statErrors      ->SetWindowText (argumentString);

    argumentString.Format ("%d", m_failures);
    statFailures    ->SetWindowText (argumentString);

    argumentString.Format ("Execution time: %3.3lf seconds", (m_testEndTime - m_testStartTime) / 1000.0);
    editTime        ->SetWindowText (argumentString);


}

void TestRunnerDlg::OnStop() 
{
    if (m_result)
        m_result->stop ();

    beIdle ();
}

void TestRunnerDlg::OnOK() 
{
    if (m_result)
        m_result->stop ();

    CDialog::OnOK ();
}


void 
TestRunnerDlg::OnSelchangeComboTest() 
{
  int currentSelection = getHistoryCombo()->GetCurSel ();

  if ( currentSelection >= 0  &&
       currentSelection < m_model->history().size() )
  {
    CppUnit::Test *selectedTest = m_model->history()[currentSelection];
    m_model->selectHistoryTest( selectedTest );
    updateHistoryCombo();
    beIdle();
  }
  else
    beRunDisabled();
}


void
TestRunnerDlg::updateHistoryCombo()
{
  getHistoryCombo()->LockWindowUpdate();

  getHistoryCombo()->ResetContent();

  const TestRunnerModel::History &history = m_model->history();
  for ( TestRunnerModel::History::const_iterator it = history.begin(); 
        it != history.end(); 
        ++it )
  {
    CppUnit::Test *test = *it;
    getHistoryCombo()->AddString( test->getName().c_str() );
  }

  if ( history.size() > 0 )
  {
    getHistoryCombo()->SetCurSel( 0 );
    beIdle();
  }
  else
    beRunDisabled();

  getHistoryCombo()->UnlockWindowUpdate();
}


void 
TestRunnerDlg::OnPaint() 
{
  CPaintDC dc (this); 
  
  m_testsProgress->paint(dc);
}


void 
TestRunnerDlg::OnBrowseTest() 
{
  TreeHierarchyDlg dlg;
  dlg.setRootTest( m_model->rootTest() );
  if ( dlg.DoModal() == IDOK )
  {
    m_model->selectHistoryTest( dlg.getSelectedTest() );
    updateHistoryCombo();
  }
}


BOOL 
TestRunnerDlg::PreTranslateMessage(MSG* pMsg) 
{
  if ( ::TranslateAccelerator( m_hWnd,
                               m_hAccelerator,
                               pMsg ) )
  {
    return TRUE;
  }
  return CDialog::PreTranslateMessage(pMsg);
}


CComboBox *
TestRunnerDlg::getHistoryCombo()
{
  CComboBox   *comboBox = (CComboBox *)GetDlgItem (IDC_COMBO_TEST);
  ASSERT (comboBox);
  return comboBox;
}


void
TestRunnerDlg::loadSettings()
{
  m_model->loadSettings();

  m_bAutorunAtStartup = m_model->autorunOnLaunch();
}


void
TestRunnerDlg::saveSettings()
{
  m_model->setAutorunOnLaunch( m_bAutorunAtStartup != 0 );
  
  m_model->saveSettings();
}


void 
TestRunnerDlg::OnQuitApplication() 
{
  CWinApp *app = AfxGetApp();
  ASSERT( app != NULL );
  app->PostThreadMessage( WM_QUIT, 0, 0 );
}


TestRunnerModel &
TestRunnerDlg::model()
{
  ASSERT( m_model != NULL );
  return *m_model;
}

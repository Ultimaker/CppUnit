#if !defined(AFX_TREEHIERARCHYDLG_H__81E65BC0_1F91_482C_A8BD_C1EC305CD6DA__INCLUDED_)
#define AFX_TREEHIERARCHYDLG_H__81E65BC0_1F91_482C_A8BD_C1EC305CD6DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeHierarchyDlg.h : header file
//

#include <cppunit/Test.h>
#include <vector>
#include "DynamicWindow/cdxCDynamicDialog.h"


/////////////////////////////////////////////////////////////////////////////
// TreeHierarchyDlg dialog

class TreeHierarchyDlg : public cdxCDynamicDialog
{
// Construction
public:
	TreeHierarchyDlg(CWnd* pParent = NULL);   // standard constructor

  void setRootTest( CppUnit::Test *test );
  CppUnit::Test *getSelectedTest() const;

  static bool isSuite( CppUnit::Test *test );

  // Dialog Data
	//{{AFX_DATA(TreeHierarchyDlg)
	CTreeCtrl	m_treeTests;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TreeHierarchyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  virtual void initializeLayout();
  void storeDialogBounds();

	// Generated message map functions
	//{{AFX_MSG(TreeHierarchyDlg)
	virtual BOOL OnInitDialog();
  virtual void OnOK( );
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

private:
  typedef std::vector<CppUnit::Test *> Tests;

  void fillTree();
  HTREEITEM addTest( CppUnit::Test *test, 
                     HTREEITEM hParent );
  void addTestSuiteChildrenTo( CppUnit::Test *suite,
                               HTREEITEM hItemSuite );

  void sortByName( Tests &tests ) const;
  CppUnit::Test *findSelectedTest();

  enum
  {
    imgSuite =0,
    imgUnitTest,
  };

  CImageList m_imageList;
  CppUnit::Test *m_selectedTest;
  CppUnit::Test *m_rootTest;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEHIERARCHYDLG_H__81E65BC0_1F91_482C_A8BD_C1EC305CD6DA__INCLUDED_)

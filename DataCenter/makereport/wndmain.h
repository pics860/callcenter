//
// WndMain.h
//

#if !defined(AFX_WNDMAIN_H__B7029645_0B22_4BD4_B8E1_48491100728B__INCLUDED_)
#define AFX_WNDMAIN_H__B7029645_0B22_4BD4_B8E1_48491100728B__INCLUDED_

#pragma once

#include "WindowManager.h"
#include "CtrlCoolBar.h"
#include "CtrlCoolMenuBar.h"

/////////////////////////////////////////////////////////////////////////////
// CMainWnd frame

class CMainWnd : public CMDIFrameWnd
{
// Construction
public:
	CMainWnd();
	virtual ~CMainWnd();

	DECLARE_DYNCREATE(CMainWnd)

// Attributes
public:
	CWindowManager		m_pWindows;
protected:
	CCoolMenuBarCtrl	m_wndMenuBar;
	CCoolBarCtrl		m_wndToolBar;
	CStatusBar			m_wndStatusBar;
protected:
	BOOL				m_bInTimer;

// Operations
public:
	CChildWnd*	GetWindow(CRuntimeClass* pClass);
protected:

// Overrides
public:
	//{{AFX_VIRTUAL(CMainWnd)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CMainWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnUpdateWindowToolBar(CCmdUI* pCmdUI);
	afx_msg void OnWindowToolBar();
	afx_msg void OnUpdateWindowStatusBar(CCmdUI* pCmdUI);
	afx_msg void OnWindowStatusBar();
	afx_msg void OnUpdateWindowDebug(CCmdUI* pCmdUI);
	afx_msg void OnWindowDebug();
	afx_msg void OnUpdateTabUnicom(CCmdUI* pCmdUI);
	afx_msg void OnTabUnicom();
	afx_msg void OnUpdateTabTelecom(CCmdUI* pCmdUI);
	afx_msg void OnTabTelecom();
	afx_msg void OnToolsSettings();
	afx_msg void OnToolsProfiles();
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

AFX_INLINE CChildWnd* CMainWnd::GetWindow(CRuntimeClass* pClass)
{
	return m_pWindows.Find( pClass );
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#define IDW_MENU_BAR		0xE810
#define IDW_TOOL_BAR		AFX_IDW_TOOLBAR
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDMAIN_H__B7029645_0B22_4BD4_B8E1_48491100728B__INCLUDED_)

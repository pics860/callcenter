//
// CtrlTelecomPanel.cpp
//

#include "stdafx.h"
#include "MakeReport.h"
#include "CoolInterface.h"
#include "CtrlTelecomPanel.h"
#include "Settings.h"

#include "WndTelecom.h"
#include "DlgProfilesManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTelecomPanel, CTaskPanel)
BEGIN_MESSAGE_MAP(CTelecomPanel, CTaskPanel)
	//{{AFX_MSG_MAP(CTelecomPanel)
	ON_WM_CREATE()
	ON_MESSAGE(WM_NEXTMONTH, OnNextMonth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CTelecomTaskBox, CTaskBox)
BEGIN_MESSAGE_MAP(CTelecomTaskBox, CTaskBox)
	//{{AFX_MSG_MAP(CTelecomTaskBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDC_TELECOM_START, OnStart)
	ON_COMMAND(IDC_TELECOM_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CTelecomResultBox, CTaskBox)
BEGIN_MESSAGE_MAP(CTelecomResultBox, CTaskBox)
	//{{AFX_MSG_MAP(CTelecomResultBox)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_TIMEROUT, OnTimerOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define BOX_MARGIN	10

/////////////////////////////////////////////////////////////////////////////
// CTelecomPanel construction

CTelecomPanel::CTelecomPanel()
{
}

CTelecomPanel::~CTelecomPanel()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTelecomPanel operations

void CTelecomPanel::ExecuteStart()
{
	m_wndTask.SendMessage( WM_COMMAND, IDC_TELECOM_START );
}

void CTelecomPanel::ExecuteClear()
{
	m_wndTask.SendMessage( WM_COMMAND, IDC_TELECOM_CLEAR );
}

void CTelecomPanel::ExecuteNextMonth()
{
	m_wndTask.SendMessage( WM_COMMAND, IDC_TELECOM_CLEAR );
	
	m_wndTask.ExecuteContinue();
}

#if 0
void CTelecomPanel::ExecuteFlowBack(DWORD nFlowCount)
{
	m_wndResult.m_wndClock.SetStyle( CEDClock::EClockStyle::XDC_FLOWBACK, nFlowCount );
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CTelecomPanel message handlers

BOOL CTelecomPanel::Create(CWnd* pParentWnd)
{
	return CTaskPanel::Create( WS_VISIBLE, CRect(0,0,0,0), pParentWnd, IDC_TELECOM_PANEL );
}

int CTelecomPanel::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if ( CTaskPanel::OnCreate( lpCreateStruct ) == -1 )return -1;
	
	m_wndTask.Create( this, 112, _T("任务"), IDI_TASKPANEL );
	m_wndResult.Create( this, 48, _T("结果"), IDI_SEARCH_FOLDER );
	
	AddBox( &m_wndTask );
	AddBox( &m_wndResult );

	return 0;
}

LONG CTelecomPanel::OnNextMonth(WPARAM wParam, LPARAM lParam)
{
	ExecuteNextMonth();
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CTelecomTaskBox construction

CTelecomTaskBox::CTelecomTaskBox()
{
	m_crClient = CoolInterface.m_crTaskBoxClient;
	m_brClient.CreateSolidBrush( m_crClient );
}

CTelecomTaskBox::~CTelecomTaskBox()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTelecomTaskBox message handlers

int CTelecomTaskBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if ( CTaskBox::OnCreate( lpCreateStruct ) == -1 ) return -1;
	
	CRect rc( 0, 0, 0, 0 );
	
	m_wndMode.Create( WS_CHILD|WS_VSCROLL|WS_VISIBLE|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_HASSTRINGS,//|CBS_SORT,
		rc, this, IDC_TELECOM_MODE );
	
	m_wndMode.AddString( "立即执行");
	m_wndMode.AddString( "下月1日零时30分");
	m_wndMode.SetFont( &CoolInterface.m_fntNormal );
	m_wndMode.SetCurSel( 0 );
	
	m_wndProfile.Create( "修正计费规则", WS_CHILD|WS_VISIBLE, rc, this );
	m_wndProfile.SetFont( &CoolInterface.m_fntNormal );
	
	m_wndStart.Create( rc, this, IDC_TELECOM_START );
	m_wndStart.SetWindowText( "开始执行" );
	m_wndStart.SetIcon( CoolInterface.m_pImages.ExtractIcon( 22 ) );
	m_wndStart.SetHandCursor( TRUE );
	
	m_wndClear.Create( rc, this, IDC_TELECOM_CLEAR );
	m_wndClear.SetWindowText( "停止" );
	m_wndClear.SetIcon( CoolInterface.m_pImages.ExtractIcon( 7 ) );
	m_wndClear.SetHandCursor( TRUE );
	
	SetPrimary( TRUE );
	
	return 0;
}

void CTelecomTaskBox::OnDestroy()
{
}

void CTelecomTaskBox::OnSize(UINT nType, int cx, int cy) 
{
	CTaskBox::OnSize( nType, cx, cy );
	
	HDWP hDWP = BeginDeferWindowPos( 4 );
	
	DeferWindowPos( hDWP, m_wndMode, NULL, BOX_MARGIN, 27,
		cx - BOX_MARGIN * 2, 256, SWP_NOZORDER );
	
	DeferWindowPos( hDWP, m_wndProfile, NULL, BOX_MARGIN + 42, BOX_MARGIN + 52,
		cx - BOX_MARGIN * 2 - 74, 16, SWP_NOZORDER );
	
	DeferWindowPos( hDWP, m_wndStart, NULL, BOX_MARGIN, 82, 86, 24, SWP_SHOWWINDOW|SWP_NOZORDER );
	DeferWindowPos( hDWP, m_wndClear, NULL, BOX_MARGIN + 94, 82, 60, 24, SWP_SHOWWINDOW|SWP_NOZORDER );
	
	EndDeferWindowPos( hDWP );
}

void CTelecomTaskBox::OnPaint() 
{
	CPaintDC dc( this );
	CRect rc, rct;
	CString str;
	
	UINT nFlags = ETO_CLIPPED;
	CDC* pDC = &dc;
	
	GetClientRect( &rc );
	
	if ( m_bmWatermark.m_hObject != NULL )
	{
		pDC = CoolInterface.GetBuffer( dc, rc.Size() );
		CoolInterface.DrawWatermark( pDC, &rc, &m_bmWatermark );
		pDC->SetBkMode( TRANSPARENT );
	}
	else
	{
		pDC->SetBkMode( OPAQUE );
		pDC->SetBkColor( CoolInterface.m_crTaskBoxClient );
		nFlags |= ETO_OPAQUE;
	}
	
	CFont* pOldFont = (CFont*)pDC->SelectObject( &CoolInterface.m_fntNormal );
	
	pDC->SetTextColor( 0 );
	
	rct.SetRect( BOX_MARGIN + 1, BOX_MARGIN, rc.right - BOX_MARGIN, BOX_MARGIN + 16 );
	pDC->ExtTextOut( rct.left, rct.top, nFlags, &rct, "请选择执行方式:", NULL );
	pDC->ExcludeClipRect( &rct );
	
	pDC->SelectObject( pOldFont );
	
	if ( pDC != &dc )
	{
		dc.BitBlt( 0, 0, rc.Width(), rc.Height(), pDC, 0, 0, SRCCOPY );
		pDC->SelectClipRgn( NULL );
	}
	else
	{
		pDC->FillSolidRect( &rc, CoolInterface.m_crTaskBoxClient );
	}
}

HBRUSH CTelecomTaskBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = (HBRUSH)CTaskBox::OnCtlColor( pDC, pWnd, nCtlColor );
	
	pDC->SetBkColor( CoolInterface.m_crTaskBoxClient );
	
	if ( pWnd == &m_wndProfile )
	{
		pDC->SetTextColor( RGB( 0, 0, 255 ) );
		pDC->SelectObject( &CoolInterface.m_fntUnder );
	}
	
	return m_brClient;
}

BOOL CTelecomTaskBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CPoint point;
	CRect rc;

	GetCursorPos( &point );
	m_wndProfile.GetWindowRect( &rc );

	if ( rc.PtInRect( point ) )
	{
		SetCursor( theApp.LoadCursor( IDC_HAND ) );
		return TRUE;
	}
	
	return CTaskBox::OnSetCursor( pWnd, nHitTest, message );
}

void CTelecomTaskBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTaskBox::OnLButtonUp( nFlags, point );
	
	CRect rc;
	m_wndProfile.GetWindowRect( &rc );
	ScreenToClient( &rc );
	
	if ( rc.PtInRect( point ) )
	{
		CProfilesManagerDlg::Run( _T("CTelecomSettingsPage") );
	}
}

void CTelecomTaskBox::OnStart()
{
	DWORD nFlowCount = 0;
	
	if ( m_wndMode.GetCurSel() == 1 )
	{
		CTime tNextMonth;
		CTime tNow = CTime::GetCurrentTime();
		
		// 下月1日0时30分
		if ( tNow.GetMonth() == 12 )
			tNextMonth = CTime( tNow.GetYear()+1, 1, 1, 0, 30, 0 );
		else
			tNextMonth = CTime( tNow.GetYear(), tNow.GetMonth()+1, 1, 0, 30, 0 );
		
		nFlowCount = (tNextMonth - tNow).GetTotalSeconds();
	}
	
	if ( CTaskBox* pTaskBox = GetPanel()->FindBox( RUNTIME_CLASS(CTelecomResultBox) ) )
	{
		((CTelecomResultBox*)pTaskBox)->m_wndClock.SetStyle( CEDClock::EClockStyle::XDC_FLOWBACK, nFlowCount );
	}
	
	m_wndMode.EnableWindow( FALSE );
	m_wndStart.SetWindowText( "运行中...");
	m_wndStart.EnableWindow( FALSE );
}

void CTelecomTaskBox::OnClear()
{
	if ( m_wndStart.IsWindowEnabled() ) return;
	
	m_wndMode.EnableWindow( TRUE );
	m_wndStart.SetWindowText( "开始执行");
	m_wndStart.EnableWindow( TRUE );
	
	if ( CTaskBox* pTaskBox = GetPanel()->FindBox( RUNTIME_CLASS(CTelecomResultBox) ) )
	{
		((CTelecomResultBox*)pTaskBox)->m_wndClock.SetStyle( CEDClock::EClockStyle::XDC_NORMAL );
	}
	
	GetPanel()->GetParent()->SendMessage( ID_TAB_CONNECT, -1 );
}

void CTelecomTaskBox::ExecuteContinue()
{
	m_wndMode.SetCurSel( 1 );
	PostMessage( WM_COMMAND, IDC_TELECOM_START );
}

/////////////////////////////////////////////////////////////////////////////
// CTelecomResultBox construction

CTelecomResultBox::CTelecomResultBox()
{
}

CTelecomResultBox::~CTelecomResultBox()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTelecomResultBox message handlers

int CTelecomResultBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if ( CTaskBox::OnCreate( lpCreateStruct ) == -1 ) return -1;
	
	CRect rc( 0, 0, 0, 0 );
	
	m_wndClock.Create( WS_CHILD|WS_VISIBLE, rc, this, IDC_TELECOM_CLOCK);
	
	SetTimer( 5, 1000, NULL );
	PostMessage( WM_TIMER, 5 );
	
	return 0;
}

void CTelecomResultBox::OnDestroy()
{
}

void CTelecomResultBox::OnSize(UINT nType, int cx, int cy) 
{
	CTaskBox::OnSize( nType, cx, cy );
	
	HDWP hDWP = BeginDeferWindowPos( 1 );
	
	DeferWindowPos( hDWP, m_wndClock, NULL, BOX_MARGIN + 49, 7,
		13 * 8, 23, SWP_NOZORDER );
	
	EndDeferWindowPos( hDWP );
}

void CTelecomResultBox::OnPaint() 
{
	CPaintDC dc( this );
	CRect rc, rct;
	CString str;
	
	UINT nFlags = ETO_CLIPPED;
	CDC* pDC = &dc;
	
	GetClientRect( &rc );
	
	if ( m_bmWatermark.m_hObject != NULL )
	{
		pDC = CoolInterface.GetBuffer( dc, rc.Size() );
		CoolInterface.DrawWatermark( pDC, &rc, &m_bmWatermark );
		pDC->SetBkMode( TRANSPARENT );
	}
	else
	{
		pDC->SetBkMode( OPAQUE );
		pDC->SetBkColor( CoolInterface.m_crTaskBoxClient );
		nFlags |= ETO_OPAQUE;
	}
	
	CFont* pOldFont = (CFont*)pDC->SelectObject( &CoolInterface.m_fntNormal );
	
	pDC->SetTextColor( 0 );
	
	rct.SetRect( BOX_MARGIN + 1, BOX_MARGIN + 3, rc.right - BOX_MARGIN, BOX_MARGIN + 16 );
	pDC->ExtTextOut( rct.left, rct.top, nFlags, &rct, "您还剩:", NULL );
	pDC->ExcludeClipRect( &rct );
	
	pDC->SelectObject( pOldFont );
	
	if ( pDC != &dc )
	{
		dc.BitBlt( 0, 0, rc.Width(), rc.Height(), pDC, 0, 0, SRCCOPY );
		pDC->SelectClipRgn( NULL );
	}
	else
	{
		pDC->FillSolidRect( &rc, CoolInterface.m_crTaskBoxClient );
	}
}

LONG CTelecomResultBox::OnTimerOut(WPARAM wParam, LPARAM lParam)
{
	m_wndClock.SetStyle( CEDClock::EClockStyle::XDC_FLOWNEXT );
	GetPanel()->GetParent()->PostMessage( ID_TAB_CONNECT );
	
	return 0;
}

//
// CtrlCoolHeaderBar.h
//

#if !defined(AFX_CTRLCOOLHEADERBAR_H__22ACBAAD_EEAC_4B17_9D11_8B32C40960E3__INCLUDED_)
#define AFX_CTRLCOOLHEADERBAR_H__22ACBAAD_EEAC_4B17_9D11_8B32C40960E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ctrlcoolbar.h"

class CCoolHeaderBarCtrl : public CCoolBarCtrl  
{
// Construction
public:
	CCoolHeaderBarCtrl();
	virtual ~CCoolHeaderBarCtrl();

	DECLARE_DYNAMIC(CCoolHeaderBarCtrl)

// Attributes
protected:

// Operations
public:
	void			SetCaption(LPCTSTR pszCaption);
	void			SetIcon(HICON hIcon);
protected:
	virtual void	PrepareRect(CRect* pRect) const;
protected:
	void			PaintHeader(CDC* pDC, CRect& rcBar, BOOL bTransparent);

// Overrides
public:
	//{{AFX_VIRTUAL(CCoolHeaderBarCtrl)
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CCoolHeaderBarCtrl)
	virtual void DoPaint(CDC* pDC, CRect& rcBar, BOOL bTransparent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_CTRLCOOLHEADERBAR_H__22ACBAAD_EEAC_4B17_9D11_8B32C40960E3__INCLUDED_)

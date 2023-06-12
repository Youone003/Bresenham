// Bresenham.h : main header file for the BRESENHAM application
//

#if !defined(AFX_BRESENHAM_H__32ED2B4B_B1A2_480B_8978_DC6891F89F3C__INCLUDED_)
#define AFX_BRESENHAM_H__32ED2B4B_B1A2_480B_8978_DC6891F89F3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBresenhamApp:
// See Bresenham.cpp for the implementation of this class
//

class CBresenhamApp : public CWinApp
{
public:
	CBresenhamApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBresenhamApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBresenhamApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRESENHAM_H__32ED2B4B_B1A2_480B_8978_DC6891F89F3C__INCLUDED_)

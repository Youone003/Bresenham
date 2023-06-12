// BresenhamDlg.h : header file
//
#include "Geometry.h"
#include <vector>

#if !defined(AFX_BRESENHAMDLG_H__6147861C_8FF2_4759_BCC2_45AE4C6A549A__INCLUDED_)
#define AFX_BRESENHAMDLG_H__6147861C_8FF2_4759_BCC2_45AE4C6A549A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBresenhamDlg dialog

class CBresenhamDlg : public CDialog
{
// Construction
public:
	CBresenhamDlg(CWnd* pParent = NULL);	// standard constructor
	// 保存的需要绘制的球体
	std::vector<Sphere> spheres;
	// zbuffer
	std::vector<float> zbuffer;
	// 画布四边
	int CanvasRight, CanvasBottom, CanvasLeft, CanvasTop;
	// 画布中心的坐标（biasX, biasY），画布宽度，画布高度
	int biasX, biasY, CanvasWidth, CanvasHeight;
	// 点光源
	PointLight light;
	// 环境光
	v3f ambientColor;
	// 视点位置
	v3f viewPos;
	// 高光系数
	int ns;

	void PhongShade(const Sphere& s);
	void DrawSpheres();
	void ParseLightParams();
	void ClearCanvas();
	CClientDC* gdc;

	enum { IDD = IDD_BRESENHAM_DIALOG };

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBresenhamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRESENHAMDLG_H__6147861C_8FF2_4759_BCC2_45AE4C6A549A__INCLUDED_)

// BresenhamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bresenham.h"
#include "BresenhamDlg.h"
#include <cmath>
#include <functional>
#include <stdio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const double pi = 3.1415926;

// 向量数乘，标量数*向量
template<typename T>
v3f operator *(const T& t, const v3f& v) {
	float _t = static_cast<float>(t);
	return v3f{ v[0] * _t, v[1] * _t, v[2] * _t };
}

template<typename T>
v3f operator *(const v3f& v, const T& t) {
	return t * v;
}

// 向量相乘：v1*v2
v3f operator *(const v3f& v1, const v3f& v2) {
	return v3f{ v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2] };
}

// 向量相加：v1+v2
v3f operator +(const v3f& v1, const v3f& v2) {
	return v3f{ v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2] };
}

// 向量相减：v1-v2
v3f operator -(const v3f& v1, const v3f& v2) {
	return v1 + (-1) * v2;
}

// 向量点乘：v1·v2
float dot(const v3f& v1, const v3f& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

// 向量叉乘：v1×v2
v3f cross(const v3f& v1, const v3f& v2) {
	return v3f{ v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0] };
}

// 向量模长
float norm(const v3f& v) {
	return sqrtf(dot(v, v));
}

// 单位向量
v3f normalize(const v3f& v) {
	return 1.f / norm(v) * v;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	// Dialog Data
		//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBresenhamDlg dialog

CBresenhamDlg::CBresenhamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBresenhamDlg::IDD, pParent), CanvasRight(800), CanvasBottom(600),
	CanvasLeft(150), CanvasTop(10)
{
	//{{AFX_DATA_INIT(CBresenhamDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	biasX = (CanvasRight + CanvasLeft) / 2;
	biasY = (CanvasTop + CanvasBottom) / 2;
	CanvasWidth = CanvasRight - CanvasLeft;
	CanvasHeight = CanvasBottom - CanvasTop;
	
	viewPos = v3f{ 0, 0, 0 };
	zbuffer = std::vector<float>(CanvasWidth * CanvasHeight, 1000.f);
	
}

void CBresenhamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBresenhamDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBresenhamDlg, CDialog)
	//{{AFX_MSG_MAP(CBresenhamDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CBresenhamDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBresenhamDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CBresenhamDlg::OnBnClickedButton7)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBresenhamDlg message handlers

BOOL CBresenhamDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 初始化gdc
	gdc = new CClientDC(this);//用于画图

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBresenhamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBresenhamDlg::OnPaint()
{
	ClearCanvas();

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBresenhamDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}


void CBresenhamDlg::PhongShade(const Sphere& s) {
	// TODO: 完成Phong模型着色方法
	
	


}


// 遍历绘制每一个球
void CBresenhamDlg::DrawSpheres() {
	for (auto& s : spheres) {
		PhongShade(s);
	}
}

// 获取输入的参数
void CBresenhamDlg::ParseLightParams() {
	auto parseFloat = [this](int HDLID) {
		CString s;
		GetDlgItemText(HDLID, s);
		return static_cast<float>(atof((LPCSTR)s));
	};
	
	float LX = parseFloat(IDC_EDIT15), LY = parseFloat(IDC_EDIT16), LZ = parseFloat(IDC_EDIT17);
	float Lr = parseFloat(IDC_EDIT18), Lg = parseFloat(IDC_EDIT19), Lb = parseFloat(IDC_EDIT20);
	float Ar = parseFloat(IDC_EDIT21), Ag = parseFloat(IDC_EDIT22), Ab = parseFloat(IDC_EDIT23);
	ns = GetDlgItemInt(IDC_EDIT24);
	light = PointLight(v3f{ LX, LY, LZ }, v3f{ Lr, Lg, Lb });
	ambientColor = v3f{ Ar, Ag, Ab };
}





//鼠标左键点击
void CBresenhamDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
}

// 鼠标右键单击
void CBresenhamDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags, point);
}

// 点击【默认绘制】
void CBresenhamDlg::OnBnClickedButton2()
{
	ClearCanvas();
	spheres.clear();
	// 默认点光源
	light = PointLight(v3f{ 0,-1000,-100 }, v3f{ 1.f,1.f,1.f });
	// 三个默认球（数值根据自身的需要来改动，不一定非要和这里相同）
	spheres.push_back(Sphere(v3f{ 0,0,200 }, 50, v3f{ 0.5f, 0.5f, 0.5f }, v3f{ 0.5f, 0.5f, 0.5f }, v3f{ 1.f, 1.f, 1.f }));
	spheres.push_back(Sphere(v3f{ 100,0,200 }, 50, v3f{ 0.5f, 0.5f, 0.5f }, v3f{ 0.5f, 0.5f, 0.5f }, v3f{ 0.5f, 0.5f, 0.5f }));
	spheres.push_back(Sphere(v3f{ -100,0,200 }, 50, v3f{ 0.5f, 0.5f, 0.5f }, v3f{ 0.5f, 0.5f, 0.5f }, v3f{ 0.5f, 0.5f, 0.5f }));
	// 默认高光系数和环境光颜色
	ns = 5;
	ambientColor = v3f{ 0.2f, 0.3f, 0.4f };
	DrawSpheres();
	spheres.clear();
}

void CBresenhamDlg::ClearCanvas() {
	gdc->Rectangle(CanvasLeft, CanvasTop, CanvasRight, CanvasBottom);
	zbuffer = std::vector<float>(CanvasWidth * CanvasHeight, 1000.f);
}

// 点击【添加球体】
void CBresenhamDlg::OnBnClickedButton3()
{
	auto parseFloat = [this](int HDLID) {
		CString s;
		GetDlgItemText(HDLID, s);
		return static_cast<float>(atof((LPCSTR)s));
	};

	float CX = parseFloat(IDC_EDIT1), CY = parseFloat(IDC_EDIT2), CZ = parseFloat(IDC_EDIT5);
	int r = GetDlgItemInt(IDC_EDIT14);
	float Ksr = parseFloat(IDC_EDIT6), Ksg = parseFloat(IDC_EDIT3), Ksb = parseFloat(IDC_EDIT7);
	float Kdr = parseFloat(IDC_EDIT8), Kdg = parseFloat(IDC_EDIT9), Kdb = parseFloat(IDC_EDIT10);
	float Kar = parseFloat(IDC_EDIT11), Kag = parseFloat(IDC_EDIT12), Kab = parseFloat(IDC_EDIT13);

	spheres.push_back(Sphere(v3f{ CX, CY, CZ },
		r, v3f{ Ksr, Ksg, Ksb }, v3f{ Kdr, Kdg, Kdb }, v3f{ Kar, Kag, Kab }));
}

// 点击【自定义绘制】
void CBresenhamDlg::OnBnClickedButton7()
{
	ClearCanvas();
	ParseLightParams();
	DrawSpheres();
}



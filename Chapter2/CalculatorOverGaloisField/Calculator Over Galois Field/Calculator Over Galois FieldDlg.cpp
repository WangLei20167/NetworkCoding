
// Calculator Over Galois FieldDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator Over Galois Field.h"
#include "Calculator Over Galois FieldDlg.h"
#include "afxdialogex.h"
#include "gf.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorOverGaloisFieldDlg 对话框



CCalculatorOverGaloisFieldDlg::CCalculatorOverGaloisFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculatorOverGaloisFieldDlg::IDD, pParent)
	, m_nAlter1(0)
	, m_nAlter2(0)
	, m_nResult(0)
	

	, m_nType(0)
	
	, m_chOperator(_T(""))
	, m(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorOverGaloisFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_nAlter1);
	DDX_Text(pDX, IDC_EDIT3, m_nAlter2);
	DDX_Text(pDX, IDC_EDIT4, m_nResult);


	DDX_Text(pDX, IDC_m_chOperator, m_chOperator);
	DDX_Text(pDX, IDC_EDIT1, m);
}

BEGIN_MESSAGE_MAP(CCalculatorOverGaloisFieldDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	
	
	ON_BN_CLICKED(IDC_BUTTON_Add, &CCalculatorOverGaloisFieldDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Sub, &CCalculatorOverGaloisFieldDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_Mul, &CCalculatorOverGaloisFieldDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_Div, &CCalculatorOverGaloisFieldDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_Exp, &CCalculatorOverGaloisFieldDlg::OnBnClickedButtonExp)
	ON_BN_CLICKED(IDC_BUTTON_Cal, &CCalculatorOverGaloisFieldDlg::OnBnClickedButtonCal)
	ON_EN_CHANGE(IDC_EDIT1, &CCalculatorOverGaloisFieldDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CCalculatorOverGaloisFieldDlg 消息处理程序

BOOL CCalculatorOverGaloisFieldDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m = 8;
	m_chOperator = "+";
	m_nType = 1;
	UpdateData(FALSE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorOverGaloisFieldDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorOverGaloisFieldDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorOverGaloisFieldDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CCalculatorOverGaloisFieldDlg::OnBnClickedButtonAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nType = 1;
	m_chOperator = "+";
	UpdateData(FALSE);
}


void CCalculatorOverGaloisFieldDlg::OnBnClickedButtonSub()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nType = 2;
	m_chOperator = "-";
	UpdateData(FALSE);

}


void CCalculatorOverGaloisFieldDlg::OnBnClickedButtonMul()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nType = 3;
	m_chOperator = "*";
	UpdateData(FALSE);
}


void CCalculatorOverGaloisFieldDlg::OnBnClickedButtonDiv()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nType = 4;
	m_chOperator = "/";
	UpdateData(FALSE);
}


void CCalculatorOverGaloisFieldDlg::OnBnClickedButtonExp()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nType = 5;
	m_chOperator = "^";
	UpdateData(FALSE);
}


void CCalculatorOverGaloisFieldDlg::OnBnClickedButtonCal()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m < 0 || m>12){
		MessageBox(_T("Please input 0<m<13."));
		return;
	}
	gf_init(m, prim_poly[m]);
	if (m_nAlter1 > pow(2.0, m) || m_nAlter2 > pow(2.0, m))
	{
		MessageBox(_T("First value is greater than field size."));
		return;
	}
	if (m_nType == 1)
	{
		m_nResult = gf_add(m_nAlter1, m_nAlter2);
	}
	else if (m_nType == 2)
	{
		m_nResult = gf_sub(m_nAlter1, m_nAlter2);
	}
	else if (m_nType == 3)
	{
		m_nResult = gf_mul(m_nAlter1, m_nAlter2);
	}
	else if (m_nType == 4)
	{
		m_nResult = gf_div(m_nAlter1, m_nAlter2);
	}
	else if (m_nType == 5)
	{
		m_nResult = gf_exp(m_nAlter1, m_nAlter2);
	}
	UpdateData(FALSE);
}


void CCalculatorOverGaloisFieldDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

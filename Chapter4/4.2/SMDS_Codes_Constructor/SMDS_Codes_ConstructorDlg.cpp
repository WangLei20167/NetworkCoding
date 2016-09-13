
// SMDS_Codes_ConstructorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMDS_Codes_Constructor.h"
#include "SMDS_Codes_ConstructorDlg.h"
#include "afxdialogex.h"
#include "gf.c"

bool Snccrack(GFType **M, GFType nRow, GFType nCol);
long factorial(int a);
unsigned int C(int n, int k);
void getPos(int num, int n, int k);

long gtotal = 0;
unsigned int g_nLen = 0;
unsigned int g_nValue[50] = { 0 };

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE                          //作用：
static char THIS_FILE[] = __FILE__;
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


// CSMDS_Codes_ConstructorDlg 对话框



CSMDS_Codes_ConstructorDlg::CSMDS_Codes_ConstructorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSMDS_Codes_ConstructorDlg::IDD, pParent)
	, m_strValue1(_T(""))
	, m_strValue2(_T(""))
	, m_nK1(0)
	, m_nK2(0)
	, m_nOrder(0)
	, m_nN1(0)
	, m_nN2(0)
	
	, m_strMaxN2(_T(""))
	, m_strMaxN1(_T(""))
	, m_nK3(0)
	, m_nN3(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMDS_Codes_ConstructorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AREA1, m_strValue1);
	DDX_Text(pDX, IDC_EDIT_AREA2, m_strValue2);

	DDX_Text(pDX, IDC_EDIT_K1, m_nK1);
	DDX_Text(pDX, IDC_EDIT_K2, m_nK2);
	DDX_Text(pDX, IDC_EDIT_M, m_nOrder);
	DDX_Text(pDX, IDC_EDIT_N1, m_nN1);
	DDX_Text(pDX, IDC_EDIT_N2, m_nN2);

	DDX_Text(pDX, IDC_STATIC_Max_N2, m_strMaxN2);


	DDX_Control(pDX, IDC_EDIT_AREA1, m_AREA1);
	DDX_Control(pDX, IDC_EDIT_AREA2, m_AREA2);

	DDX_Text(pDX, IDC_STATIC_Max_N1, m_strMaxN1);
	DDX_Text(pDX, IDC_EDIT_K3, m_nK3);
	DDX_Text(pDX, IDC_EDIT_N3, m_nN3);
	DDX_Control(pDX, IDC_EDIT_AREA3, m_AREA3);
}

BEGIN_MESSAGE_MAP(CSMDS_Codes_ConstructorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_EN_CHANGE(IDC_EDIT_AREA1, &CSMDS_Codes_ConstructorDlg::OnEnChangeEditArea1)
	ON_EN_CHANGE(IDC_EDIT_AREA2, &CSMDS_Codes_ConstructorDlg::OnEnChangeEditArea2)
	ON_EN_CHANGE(IDC_EDIT_AREA3, &CSMDS_Codes_ConstructorDlg::OnEnChangeEditArea3)
	ON_BN_CLICKED(IDC_BUTTON_GET_MDS_CODE, &CSMDS_Codes_ConstructorDlg::OnBnClickedButtonGetMdsCode)
	ON_BN_CLICKED(IDC_BUTTON_GET_SMDS_CODE, &CSMDS_Codes_ConstructorDlg::OnBnClickedButtonGetSmdsCode)
	ON_BN_CLICKED(IDC_BUTTON_EVALUATE, &CSMDS_Codes_ConstructorDlg::OnBnClickedButtonEvaluate)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, &CSMDS_Codes_ConstructorDlg::OnBnClickedButtonReport)
	ON_EN_CHANGE(IDC_EDIT_M, &CSMDS_Codes_ConstructorDlg::OnEnChangeEditM)
	
	ON_BN_CLICKED(IDC_BUTTON_Random, &CSMDS_Codes_ConstructorDlg::OnBnClickedButtonRandom)
	
END_MESSAGE_MAP()


// CSMDS_Codes_ConstructorDlg 消息处理程序

BOOL CSMDS_Codes_ConstructorDlg::OnInitDialog()
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
	m_nOrder = 8;
	m_nK1 = 3;
	m_nK2 = 3;
	m_nK3 = 3;
	m_nN1 = 5;
	m_nN2 = 5;
	m_nN3 = 5;
	m_Font.CreatePointFont(100, _T("宋体"), NULL);
	m_AREA3.SetFont(&m_Font, FALSE);//     改变字体
	m_AREA1.SetFont(&m_Font, FALSE);
	m_AREA2.SetFont(&m_Font, FALSE);
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSMDS_Codes_ConstructorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSMDS_Codes_ConstructorDlg::OnPaint()
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
HCURSOR CSMDS_Codes_ConstructorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CSMDS_Codes_ConstructorDlg::PreTranslateMessage(MSG* pMsg)
{

	return CDialog::PreTranslateMessage(pMsg);
	
}


void CSMDS_Codes_ConstructorDlg::OnEnChangeEditArea1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CSMDS_Codes_ConstructorDlg::OnEnChangeEditArea2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CSMDS_Codes_ConstructorDlg::OnEnChangeEditArea3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CSMDS_Codes_ConstructorDlg::OnBnClickedButtonGetMdsCode()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// Check the values.
	if (m_nK1 == 0)
	{
		MessageBox(_T("Invalid K."));
		return;
	}
	if (m_nN1 < m_nK1)
	{
		MessageBox(_T("Please ensure that N is greater than K!"));
		return;
	}
	if (m_nOrder > 12)
	{
		return;
	}

	UINT nFieldSize = 2 << (m_nOrder - 1);

	// Get the value of N according MDS conjecture.
	UINT nMaxN = nFieldSize + 1;
	m_strMaxN1.Format(_T("%d"), nMaxN);
	bool bq2 = false;

	if ((m_nK1 == 3 || m_nK1 == (nFieldSize - 1)) && m_nOrder != 1)
	{
		nMaxN = nFieldSize + 2;
		m_strMaxN1.Format(_T("%d"), nMaxN);
		bq2 = true;
	}
	UpdateData(FALSE);
	if (m_nN1 > nMaxN)
	{
		CString message;
		CString str;
		str.Format(_T(" %u "), nMaxN);
		message = _T("Error. According to MDS conjecture, the maximal N is ") + str + _T(", the value of N you input is greater than this value. So you should enlarge the field size.");
		MessageBox(message);
		return;
	}

	// Define the required field.
	GFType prim_poly[13] =
	{
		/*	0 */	0x00000000,
		/*  1 */    0x00000001,
		/*  2 */    0x00000007,
		/*  3 */    0x0000000b,
		/*  4 */    0x00000019,
		/*  5 */    0x00000025,
		/*  6 */    0x00000043,
		/*  7 */    0x00000089,
		/*  8 */    0x00000187,
		/*  9 */    0x00000211,
		/* 10 */    0x00000409,
		/* 11 */    0x00000805,
		/* 12 */    0x00001053,
	};

	gf_init(m_nOrder, prim_poly[m_nOrder]);

	// New the storage space.
	int nRow = m_nN1;
	int nCol = m_nK1;


	int **G = new int*[nRow];
	for (int j = 0; j<nRow; j++)
	{
		G[j] = new int[nCol];
	}
	// Initialize
	int i, j;
	for (int i = 0; i<m_nN1; i++)
	{
		for (j = 0; j<m_nK1; j++)
		{
			G[i][j] = 0;
		}
	}
	if (m_nN1 >= nFieldSize)
	{
		for (i = 0; i<nFieldSize; i++)
		{
			for (j = 0; j<m_nK1; j++)
			{
				G[i][j] = gf_exp(i, j);
			}
		}
	}
	else if (m_nN1 < nFieldSize)
	{
		for (i = 0; i<m_nN1; i++)
		{
			for (j = 0; j<m_nK1; j++)
			{
				G[i][j] = gf_exp(i, j);
			}
		}
	}


	if (m_nN1 == nFieldSize + 1)
	{
		G[nFieldSize][nCol - 1] = 1;
	}
	else if (m_nN1 == nFieldSize + 2)
	{
		G[nFieldSize][nCol - 2] = 1;
		G[nFieldSize + 1][nCol - 1] = 1;
	}


	m_strValue1 = "";
	for (i = 0; i<nRow; i++)
	{
		for (j = 0; j<nCol; j++)
		{
			CString strTemp;
			strTemp.Format(_T("%3d "), G[i][j]);
			m_strValue1 += strTemp;
		}
		m_strValue1 += "\r\n";
	}
	UpdateData(false);

	gf_uninit();
	for (i = 0; i<nRow; i++)
	{
		delete[]  G[i];
	}
	delete G;

}


void CSMDS_Codes_ConstructorDlg::OnBnClickedButtonGetSmdsCode()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// Check the values.
	if (m_nOrder > 12)
	{
		return;
	}
	if (m_nK2 == 0)
	{
		MessageBox(_T("Invalid K."));
		return;
	}
	if (m_nN2 < m_nK2)
	{
		MessageBox(_T("Please ensure that N is greater than K!"));
		return;
	}


	UINT nFieldSize = 2 << (m_nOrder - 1);

	// Get the value of N according MDS conjecture.
	UINT nMaxN = nFieldSize - m_nK2 + 1;
	m_strMaxN2.Format(_T("%d"), nMaxN);
	bool bq2 = false;

	if ((m_nK2 == 3 || m_nK2 == (nFieldSize - 1)) && m_nOrder != 1)
	{
		nMaxN = nFieldSize - m_nK2 + 2;
		m_strMaxN2.Format(_T("%d"), nMaxN);
		bq2 = true;
	}
	UpdateData(FALSE);
	if (m_nN2 > nMaxN)
	{
		CString message;
		message.Format(_T("Error. The field size is not sufficient."));
		MessageBox(message);
		return;
	}

	// Define the required field.
	GFType prim_poly[13] =
	{
		/*	0 */	0x00000000,
		/*  1 */    0x00000001,
		/*  2 */    0x00000007,
		/*  3 */    0x0000000b,
		/*  4 */    0x00000019,
		/*  5 */    0x00000025,
		/*  6 */    0x00000043,
		/*  7 */    0x00000089,
		/*  8 */    0x00000187,
		/*  9 */    0x00000211,
		/* 10 */    0x00000409,
		/* 11 */    0x00000805,
		/* 12 */    0x00001053,
	};

	gf_init(m_nOrder, prim_poly[m_nOrder]);

	// New the storage space.
	int nRow = m_nN2 + m_nK2;
	int nCol = m_nK2;

	int **G = new int*[nRow];       //注意矩阵G是一个（m_nN2 + m_nK2）×m_nK2的矩阵
	for (int j = 0; j<nRow; j++)
	{
		G[j] = new int[nCol];
	}
	// Initialize
	int i, j;
	for (int i = 0; i<nRow; i++)
	{
		for (j = 0; j<nCol; j++)
		{
			G[i][j] = 0;
		}
	}
	if (nRow >= nFieldSize)
	{
		for (i = 0; i<nFieldSize; i++)
		{
			for (j = 0; j<nCol; j++)
			{
				G[i][j] = gf_exp(i, j);
			}
		}
	}
	else if (nRow < nFieldSize)
	{
		for (i = 0; i<nRow; i++)
		{
			for (j = 0; j<nCol; j++)
			{
				G[i][j] = gf_exp(i, j);
			}
		}
	}


	if (m_nN2 == nFieldSize - m_nK2 + 1)
	{
		G[nFieldSize][nCol - 1] = 1;
	}
	else if (m_nN2 == nFieldSize - m_nK2 + 2)
	{
		G[nFieldSize][nCol - 2] = 1;
		G[nFieldSize + 1][nCol - 1] = 1;
	}

	/************************************************************************/
	/*  Multiply a full rank matrix, and the full rank matrix is the inverse
	/*	of the K*K sub-matrix of Generator matrix.
	/************************************************************************/

	int **N = new int*[m_nK2];           //下面是对G矩阵前m_nK2行的求逆操作
	for (j = 0; j<m_nK2; j++)
	{
		N[j] = new int[2 * m_nK2];
	}
	for (i = 0; i<m_nK2; i++)
	{
		for (int j = 0; j<m_nK2; j++)
		{
			N[i][j] = G[i][j];
			//printf("%d\t", N[i][j]);
		}
		for (j = m_nK2; j<2 * m_nK2; j++)
		{
			if (i == j - m_nK2)
			{
				N[i][j] = 1;
			}
			else
			{
				N[i][j] = 0;
			}
			printf("%d", N[i][j]);
		}
		printf("\n");
	}
	/************************************************************************/
	/* Step 1. Change to a lower triangle matrix.                           */
	/************************************************************************/
	for (i = 0; i<nCol; i++)
	{
		for (int j = i + 1; j<nCol; j++)
		{
			// Now, the main element must be nonsingular.
			GFType temp = gf_div(N[j][i], N[i][i]);
			for (int z = 0; z<2 * nCol; z++)
			{
				N[j][z] = gf_add(N[j][z], gf_mul(temp, N[i][z]));
			}
		}
	}
	/************************************************************************/
	/* Step 2. Only the elements on the diagonal are non-zero.                  */
	/************************************************************************/
	for (i = 1; i<nCol; i++)
	{
		for (int k = 0; k<i; k++)
		{
			GFType temp = gf_div(N[k][i], N[i][i]);
			for (int z = 0; z<2 * nCol; z++)
			{
				N[k][z] = gf_add(N[k][z], gf_mul(temp, N[i][z]));
			}
		}
	}
	/************************************************************************/
	/* Step 3. The elements on the diagonal are 1.                  */
	/************************************************************************/
	for (i = 0; i<nCol; i++)
	{
		if (N[i][i] != 1)
		{
			GFType temp = N[i][i];
			for (int z = 0; z<2 * nCol; z++)
			{
				N[i][z] = gf_div(N[i][z], temp);
			}
		}
	}
	/************************************************************************/
	/* Get the new matrix.                                                  */
	/************************************************************************/

	int **CM = new int*[m_nK2];    //矩阵CM是G矩阵前m_nK2行的逆矩阵
	for (j = 0; j<m_nK2; j++)
	{
		CM[j] = new int[m_nK2];
	}
	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			CM[i][j] = N[i][j + nCol];

		}

	}
	int **GG = new int*[nRow];       //矩阵GG等于矩阵G乘以矩阵CM
	for (j = 0; j<nRow; j++)
	{
		GG[j] = new int[nCol];
	}

	for (i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			GFType temp = 0;
			for (int z = 0; z<nCol; z++)
			{
				temp = gf_add(temp, gf_mul(G[i][z], CM[z][j]));
				GG[i][j] = temp;
			}
		}
	}




	//////////////////////////////////////////////////////////////////////////
	m_strValue2 = "";
	for (i = m_nK2; i<nRow; i++)     //矩阵GG的后m_nN2行向量即是构造出来的安全编码矩阵
	{
		for (j = 0; j<nCol; j++)
		{
			CString strTemp;
			strTemp.Format(_T("%3d "), GG[i][j]);
			m_strValue2 += strTemp;
		}
		m_strValue2 += "\r\n";
	}
	UpdateData(false);

	// Clean the memory.
	gf_uninit();
	for (i = 0; i<nRow; i++)
	{
		delete[]  G[i];
		delete[]  GG[i];
	}
	delete G;
	delete GG;

	for (i = 0; i<m_nK2; i++)
	{
		delete[]  N[i];
		delete[]  CM[i];
	}
	delete N;
	delete CM;

}


void CSMDS_Codes_ConstructorDlg::OnBnClickedButtonEvaluate()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_nOrder > 12)
	{
		return;
	}
	CString winText;
	m_AREA3.GetWindowText(winText);
	winText.TrimLeft(_T(" \r\n"));
	//	winText.TrimLeft("");
	winText.TrimRight(_T("\r\n"));
	m_AREA3.SetWindowText(winText);				// Remove the lines with only a "enter" (namely "\r\n").

	if (winText == "")
	{
		MessageBox(_T("Please input a generator matrix in the following \"EDIT\". You can paste a matrix or input one manually."));
		return;
	}

	int nSize = 2 << (m_nOrder - 1);

	int nRow = 0;
	int nCol = 0;

	int i = 0;

	int nInputRow = m_AREA3.GetLineCount();
	char ch[5];
	for (int j = 0; j<nInputRow; j++)
	{
		m_AREA3.GetLine(j, (LPTSTR)ch, 1);
		if (ch[0] != '\r')
		{
			nRow++;
		}
	}												// Now, the number of the row has been obtained.


	CString str;
	m_AREA3.GetWindowText(str);
	int pos = 0;
	if (nRow >= 1)
	{
		CString temp;
		pos = str.Find(_T("\r"));
		if (pos != -1)
		{
			temp = str.Left(pos);					// The string of the first line is in temp.
		}
		else
		{
			temp = str;
		}
		temp.TrimRight(_T("\r\n"));
		temp.TrimRight(_T(" "));
		temp.TrimLeft(_T(" "));
		pos = temp.Find(_T(" "));

		while (pos != -1)
		{
			CString nStr = temp.Left(pos);
			nCol++;
			int nLen = temp.GetLength();
			temp = temp.Right(nLen - pos);
			temp.TrimLeft(_T(" "));
			pos = temp.Find(_T(" "));
		}

		nCol++;										// At last, there is no space at the end.
		// Now, we obtain the column number.
	}
	else
	{
		MessageBox(_T("The number of vector is less than 2."));
		return;
	}

	// Now, we need to define a 2-dimensional array with nRow and nCol specified.
	int  j;
	int **M = new int*[nRow];
	for (j = 0; j<nRow; j++)
	{
		M[j] = new int[nCol];
	}												// Matrix M has been provided to store all the data.

	int **MCopy = new int*[nRow];
	for (j = 0; j<nRow; j++)
	{
		MCopy[j] = new int[nCol];
	}

	bool bError = false;								// if the numbers in the matrix is not the one in the given Galois field, return!
	m_AREA3.GetWindowText(str);
	CString temp;
	for (i = 0; i<nRow; i++)
	{
		pos = str.Find(_T("\r"));
		if (pos != -1)								// reach the last row
		{
			temp = str.Left(pos);
		}
		else
		{
			temp = str;
		}
		temp.TrimRight(_T(" "));
		temp.TrimLeft(_T(" "));
		for (int j = 0; j<nCol; j++)
		{
			int pos2 = temp.Find(_T(" "));    //找到数据后面的空格，分离数据
			if (pos2 != -1)
			{
				CString str = temp.Left(pos2);
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)str);
				M[i][j] = atoi(szTemp);     //分离数据

				int nLen = temp.GetLength();
				temp = temp.Right(nLen - pos2);//取出一个数据后的剩余部分
				temp.TrimLeft(_T(" \t"));      //去掉前面的空格和制表符
			}
			else
			{
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)temp);
				M[i][j] = atoi(szTemp);
			}
			// Check whether all the numbers are in the Galois field.
			if (M[i][j] >= nSize)
			{
				bError = true;
			}

		}
		int nLen = str.GetLength();
		str = str.Right(nLen - pos - 2);				//  "\r\n" takes two positions.
	}

	if (bError == true)
	{
		MessageBox(_T("At least 1 number in the given matrix is  the element in the given Galois field."));
		// Before return, release the memory created by "new".
		for (i = 0; i<nRow; i++)
		{
			delete[]  M[i];
			delete[]  MCopy[i];
		}
		delete M;
		delete MCopy;

		return;
	}

	/************************************************************************/
	/* So far, the data has been stored in a 2-dimensional array.           */
	/************************************************************************/
	// Copy matrix M to Mcopy.	
	TRACE("\n");
	for (i = 0; i<nRow; i++)
	{
		for (j = 0; j<nCol; j++)
		{
			MCopy[i][j] = M[i][j];
			TRACE("%d ", M[i][j]);

		}
		TRACE("\n");
	}

	// Define the Galois field.
	GFType prim_poly[13] =
	{
		/*	0 */	0x00000000,
		/*  1 */    0x00000001,
		/*  2 */    0x00000007,
		/*  3 */    0x0000000b,
		/*  4 */    0x00000019,
		/*  5 */    0x00000025,
		/*  6 */    0x00000043,
		/*  7 */    0x00000089,
		/*  8 */    0x00000187,
		/*  9 */    0x00000211,
		/* 10 */    0x00000409,
		/* 11 */    0x00000805,
		/* 12 */    0x00001053,
	};
	gf_init(m_nOrder, prim_poly[m_nOrder]);

	/************************************************************************/
	/* Start to check the security!                                         */
	/************************************************************************/
	bool bLeaked = false;

	int nSecurity = 0;

	int nValue = min(nCol, nRow);

	for (int z = 1; z<nCol; z++)
	{
		if (z > nRow)
		{
			break;
		}

		int u = z;			// u represents the number of packets available to the eavesdropper.
		nSecurity = u;
		int n = nRow;
		long nCom = C(n, u);

		int *nIndex = new int[u];

		unsigned int **subM = new unsigned int*[u];
		for (j = 0; j<u; j++)
		{
			subM[j] = new unsigned int[nCol];
		}
		int nBreakPoint = 0;
		for (j = 1; j <= nCom; j++)
		{
			for (i = 0; i<u; i++)
			{
				nIndex[i] = n - u + i + 1;
			}

			int num = j;
			getPos(num, n, u);
			int nLength = g_nLen;

			int nLastValue = 0;
			for (i = 0; i<nLength; i++)
			{
				nIndex[i] = nLastValue + g_nValue[i];
				nLastValue = nIndex[i];
			}

			for (i = 0; i<50; i++)
			{
				g_nValue[i] = 0;
			}
			g_nLen = 0;

			
			for (i = 0; i<u; i++)
			{
				for (int x = 0; x<nCol; x++)
				{
					subM[i][x] = M[nIndex[i] - 1][x];
					TRACE("%d ", subM[i][x]);
				}
				TRACE("\n");
			}

			bool bRet = Snccrack((unsigned int **)subM, u, nCol);
			if (bRet == true)
			{
				bLeaked = true;
				nBreakPoint = num;
				break;
			}

		}

		if (bLeaked == true)
		{
			
			CString strSecurity;
			strSecurity.Format(_T("%d-secure network codes."), u - 1);
			MessageBox(strSecurity,_T("Check Security"));

			FILE *pFile = NULL;
			fopen_s(&pFile,"Security_Of_Code.txt", "w");
			fprintf(pFile, "The original matrix is \n");
			for (i = 0; i<nRow; i++)
			{
				for (j = 0; j<nCol; j++)
				{
					fprintf(pFile, "%4d ", M[i][j]);
				}
				fprintf(pFile, "\n");
			}
			fprintf(pFile, "\n");
			fprintf(pFile, "The required field size is GF(%d)\n", nSize);
			fprintf(pFile, "Row=%d, Multicast capacity h=Column=%d\n", nRow, nCol);
			for (i = 1; i <= u - 1; i++)
			{
				fprintf(pFile, "u=%d: Satisfied!,C(%d,%d)=%d different combinations have been tested.\n", i, nRow, i, C(nRow, i));
			}
			fprintf(pFile, "\n");
			fprintf(pFile, "However, when u=%d, some meaningful information leaks.\n", u);
			fprintf(pFile, "There are C(%d,%d)=%d different combinations, when we proceed to the %d-th combination, some meaningful information leaks.\n", nRow, u, C(nRow, i), nBreakPoint);
			fprintf(pFile, "\n");
			fprintf(pFile, "This combination of vectors doesn't satisfy the condition of %d-secure network codes\n", u);
			for (i = 0; i<u; i++)
			{
				fprintf(pFile, "%d ", nIndex[i]);
			}
			fprintf(pFile, "\n");

			fprintf(pFile, "These row vectors will form a matrix shown as follows.\n");

			for (i = 0; i<u; i++)
			{
				for (j = 0; j<nCol; j++)
				{
					fprintf(pFile, "%4d ", M[nIndex[i] - 1][j]);
				}
				fprintf(pFile, "\n");
			}
			fprintf(pFile, "\n");

			fprintf(pFile, "This matrix can be translated into the following matrix after elementary row transformation.\n");
			for (i = 0; i<u; i++)
			{
				for (j = 0; j<nCol; j++)
				{
					fprintf(pFile, "%4d ", subM[i][j]);
				}
				fprintf(pFile, "\n");
			}
			fprintf(pFile, "\n");
			fprintf(pFile, "There is a vector with only one non-zero element in the new matrix, which implies that the eavesdropper can obtain some meaningful information.");
			fprintf(pFile, "Therefore, the network codes constructed by this generator matrix only satisfy the condition of %d-secure network codes.\n", u - 1);
			fclose(pFile);



			break;
		}


		delete[] nIndex;
		for (i = 0; i<u; i++)
		{
			delete[]  subM[i];
		}
		delete subM;

	}

	if (bLeaked == false)
	{
		
		CString strSecurity;
		strSecurity.Format(_T("%d-secure network codes."), nSecurity);
		MessageBox(strSecurity, _T("Check Security"));
	

		FILE *pFile = NULL;
		fopen_s(&pFile,"Security_Of_Code.txt", "w");
		fprintf(pFile, "Secure! %d-secure network codes!\n", nSecurity);
		fprintf(pFile, "The required field size is GF(%d)\n", nSize);
		fprintf(pFile, "Row=%d, Multicast capacity h=Column=%d\n", nRow, nCol);
		for (i = 1; i <= nSecurity; i++)
		{
			fprintf(pFile, "u=%d: Satisfied! %d different combinations have been tested.\n", i, C(nRow, i));
		}
		fprintf(pFile, "Where, u is the number of packets available to the eavesdropper.");
		fclose(pFile);
	}

	gf_uninit();
	for (i = 0; i<nRow; i++)
	{
		delete[]  M[i];
		delete[]  MCopy[i];
	}
	delete M;
	delete MCopy;



}


void CSMDS_Codes_ConstructorDlg::OnBnClickedButtonReport()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, _T("open"), _T("Security_Of_Code.txt"), NULL, NULL, SW_SHOWNORMAL);
}

long factorial(int a)
{
	long res = 1;
	for (int i = 1; i <= a; i++)
	{
		res *= i;
	}
	return res;
}

unsigned int C(int n, int k)
{
	// Get the number of all combinations.
	if (k<(n - k))
	{
		k = n - k;
	}

	bool *bVal = new bool[n - k];
	for (int i = 0; i<n - k; i++)
	{
		bVal[i] = false;
	}
	int d = n - k;
	int nn = n;
	long sum = 1;
	int i, j;
	while (d)
	{
		sum *= nn;
		nn--;
		d--;
		/////
		for (i = 0; i<n - k; i++)
		{
			if (bVal[i] == true)
			{
				continue;
			}
			else
			{
				if (sum % (i + 1) == 0)
				{
					sum = sum / (i + 1);
					bVal[i] = true;
				}
			}
		}


	}
	delete bVal;
	return sum;

}

bool Snccrack(GFType **G, GFType nRow, GFType nCol)
{
	int **M = new int*[nRow];
	for (int j = 0; j<nRow; j++)
	{
		M[j] = new int[nCol];
	}


	for (int i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			//			TRACE("%d\t", *(*G + nCol*i + j));//
			M[i][j] = *(*(G + i) + j);
		}
		//		TRACE("\n");
	}
	// printf("\n");
	//		TRACE("&&&\n");
	int i, j;
	for (i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			TRACE("%d\t", M[i][j]);
		}
		TRACE("\n");
	}
	TRACE("\n");

	// Define a variable to record the position of the main element.
	int yPos = 0;

	for (i = 0; i<nRow; i++)
	{
		// Find the main element which must be non-zero.

		bool bFind = false;

		for (int x = yPos; x<nCol; x++)
		{
			for (int k = i; k<nRow; k++)
			{
				if (M[k][x] != 0)
				{
					// Exchange the two vectors.
					for (int x = 0; x<nCol; x++)
					{
						int nVal = M[i][x];
						M[i][x] = M[k][x];
						M[k][x] = nVal;
					}										// We have exchanged the two vectors.	
					bFind = true;
					break;
				}
			}
			if (bFind == true)
			{
				yPos = x;
				break;
			}
		}



		for (int j = i + 1; j<nRow; j++)
		{
			// Now, the main element must be nonsingular.
			GFType temp = gf_div(M[j][yPos], M[i][yPos]);
			for (int z = 0; z<nCol; z++)
			{
				M[j][z] = gf_add(M[j][z], gf_mul(temp, M[i][z]));
			}
		}
		// 
		yPos++;

	}

	// The matrix becomes a scalar matrix. we need to make more elements become 0 with elementary transformations.
	yPos = 0;
	for (i = 1; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			if (M[i][j] != 0)
			{
				// the main element is found.
				yPos = j;
				break;
			}
		}
		for (int k = 0; k<i; k++)
		{
			GFType temp = gf_div(M[k][yPos], M[i][yPos]);
			for (int z = 0; z<nCol; z++)
			{
				M[k][z] = gf_add(M[k][z], gf_mul(temp, M[i][z]));
			}
		}
	}

	for (i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			TRACE("%d\t", M[i][j]);
		}
		TRACE("\n");
	}
	TRACE("\n");

	bool bLeaked = false;
	// Check whether there is an identity vector in the matrix after elementary transformation of matrix. 
	for (i = 0; i<nRow; i++)
	{
		int nNonzero = 0;
		for (j = 0; j<nCol; j++)
		{
			if (M[i][j] != 0)
			{
				nNonzero++;
			}

		}
		// If there is only one nonzero element in the new matrix, it is concluded an original packet is leaked. 
		if (nNonzero == 1)
		{
			// Leaked.
			bLeaked = true;

			for (int i = 0; i<nRow; i++)
			{
				for (int j = 0; j<nCol; j++)
				{
					*(*(G + i) + j) = M[i][j];
				}
				//		TRACE("\n");
			}
			break;
		}
	}

	/*	if (bLeaked == true)
	{
	for (i=0; i<nRow; i++)
	{
	for (int j=0; j<nCol; j++)
	{
	printf("%d\t", M[i][j]);
	}
	printf("\n");
	}
	printf("\n");
	}
	*/

	for (i = 0; i<nRow; i++)
	{
		delete[]  M[i];
	}
	delete[] M;

	return bLeaked;
}

void getPos(int num, int n, int k)
{
	int nPos = 1;

	while (num > C(n - 1, k - 1))
	{

		num -= C(n - 1, k - 1);
		n--;
		nPos += 1;

	}

	//	printf("%d \n", nPos);

	g_nValue[g_nLen] = nPos;
	g_nLen++;

	if (num == C(n - 1, k - 1))
	{
		return;
	}

	getPos(num, n - 1, k - 1);


	return;

}



void CSMDS_Codes_ConstructorDlg::OnEnChangeEditM()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.


	// TODO:  Add your control notification handler code here
}





void CSMDS_Codes_ConstructorDlg::OnBnClickedButtonRandom()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int nRow = m_nN3;
	int nCol = m_nK3;

	CString m_strValue3("");
	srand(time(NULL));

	for (int i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			CString strTemp;
			strTemp.Format(_T("%3d "), rand() % (2 << (m_nOrder - 1)));
			m_strValue3 += strTemp;
		}
		m_strValue3 += "\r\n";
	}

	m_AREA3.SetWindowText(m_strValue3);
}




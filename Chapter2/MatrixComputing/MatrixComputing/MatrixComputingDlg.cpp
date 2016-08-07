
// MatrixComputingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MatrixComputing.h"
#include "MatrixComputingDlg.h"
#include "afxdialogex.h"
#include "gf.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum{ ADD = 1,MULTIPLY};
unsigned int Rank(GFType **G, GFType nRow, GFType nCol);


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMatrixComputingDlg dialog



CMatrixComputingDlg::CMatrixComputingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMatrixComputingDlg::IDD, pParent)
	, nOperation(0)
	, m_nOrder(0)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatrixComputingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EditLeft, m_Matrix);
	//  DDX_Text(pDX, IDC_EditMiddle, m_Matrix2);
	//  DDX_Text(pDX, IDC_EditRight, m_Matrix3);
	DDX_Text(pDX, IDC_Order, m_nOrder);
	DDX_Control(pDX, IDC_EditLeft, m_Matrix);
	DDX_Control(pDX, IDC_EditMiddle, m_Matrix2);
	DDX_Control(pDX, IDC_EditRight, m_Matrix3);
}

BEGIN_MESSAGE_MAP(CMatrixComputingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Transpose, &CMatrixComputingDlg::OnBnClickedTranspose)
	ON_BN_CLICKED(IDC_Inverse, &CMatrixComputingDlg::OnBnClickedInverse)
	ON_BN_CLICKED(IDC_Add, &CMatrixComputingDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_Multiply, &CMatrixComputingDlg::OnBnClickedMultiply)
	ON_EN_CHANGE(IDC_Order, &CMatrixComputingDlg::OnEnChangeOrder)
	ON_EN_CHANGE(IDC_EditLeft, &CMatrixComputingDlg::OnEnChangeEditleft)
END_MESSAGE_MAP()


// CMatrixComputingDlg message handlers

BOOL CMatrixComputingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_nOrder = 4;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMatrixComputingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMatrixComputingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMatrixComputingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatrixComputingDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}


void CMatrixComputingDlg::compute()
{
	UpdateData(true);
	if (m_nOrder > 12)
	{
		return;
	}
	CString winText, winText2;
	m_Matrix.GetWindowText(winText);
	winText.TrimLeft(_T(" \r\n"));
	winText.TrimRight(_T("\r\n"));
	m_Matrix.SetWindowText(winText);

	m_Matrix2.GetWindowText(winText2);
	winText2.TrimLeft(_T(" \r\n"));
	winText2.TrimRight(_T("\r\n"));
	m_Matrix2.SetWindowText(winText2);			// Remove the lines with only a "enter" (namely "\r\n").

	if (winText == "")
	{
		MessageBox(_T("Please input a generator matrix in the following \"EDIT\". You can paste a matrix or input one manually."));
		return;
	}

	int nSize = 2 << (m_nOrder - 1);

	int nRow = 0;
	int nCol = 0;

	int nRow2 = 0;
	int nCol2 = 0;

	int i = 0;

	int nInputRow = m_Matrix.GetLineCount();
	char ch[5];
	for (int j = 0; j<nInputRow; j++)
	{
		m_Matrix.GetLine(j, (LPTSTR)ch, 1);
		if (ch[0] != '\r')
		{
			nRow++;
		}
	}
	for (int j = 0; j<m_Matrix2.GetLineCount(); j++)
	{
		m_Matrix2.GetLine(j, (LPTSTR)ch, 1);
		if (ch[0] != '\r')
		{
			nRow2++;
		}
	}										// Now, the number of the row has been obtained.


	CString str;
	m_Matrix.GetWindowText(str);
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

	m_Matrix2.GetWindowText(str);
	pos = 0;
	if (nRow2 >= 1)
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
			nCol2++;
			int nLen = temp.GetLength();
			temp = temp.Right(nLen - pos);
			temp.TrimLeft(_T(" "));
			pos = temp.Find(_T(" "));
		}

		nCol2++;										// At last, there is no space at the end.
		// Now, we obtain the column number.
	}

	if (nOperation == ADD)
	{
		if (nCol2 != nCol || nRow2 != nRow)
		{
			MessageBox(_T("The numbers of row and column for the two matrix must the same."));
			return;
		}

	}
	else if (nOperation == MULTIPLY)
	{
		if (nCol != nRow2)
		{
			MessageBox(_T("The column number of the left matrix must be equal to the row number of the right matrix."));
			return;
		}
	}


	// Now, we need to define a 2-dimensional array with nRow and nCol specified.

	int **M = new int*[nRow];
	for (int j = 0; j < nRow; j++)
	{
		M[j] = new int[nCol];
	}												// Matrix M has been provided to store all the data.
	int **N = new int*[nRow2];
	for (int j = 0; j < nRow2; j++)
	{
		N[j] = new int[nCol2];
	}

	bool bError = false;								// if the numbers in the matrix is not the one in the given Galois field, return!
	m_Matrix.GetWindowText(str);
	CString temp;
	for (i = 0; i < nRow; i++)
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
		for (int j = 0; j < nCol; j++)
		{
			int pos2 = temp.Find(_T(" "));
			if (pos2 != -1)
			{
				CString str = temp.Left(pos2);
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)str);
				M[i][j] = atoi(szTemp);

				int nLen = temp.GetLength();
				temp = temp.Right(nLen - pos2);
				temp.TrimLeft(_T(" "));
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
		if (pos != -1)
		{
			int nLen = str.GetLength();
			str = str.Right(nLen - pos - 2);				//  "\r\n" takes two positions.
		}
		else
		{
			str = _T("");
		}


	}

	m_Matrix2.GetWindowText(str);
	for (i = 0; i<nRow2; i++)
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
		for (int j = 0; j<nCol2; j++)
		{
			int pos2 = temp.Find(_T(" "));
			if (pos2 != -1)
			{
				CString str = temp.Left(pos2);
				char szTemp[20] = { 0 };
				::wsprintfA(szTemp, "%ls", (LPCTSTR)str);

				N[i][j] = atoi(szTemp);
				int nLen = temp.GetLength();
				temp = temp.Right(nLen - pos2);
				temp.TrimLeft(_T(" "));
			}

			else
			{
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)temp);
				N[i][j] = atoi(szTemp);
			}

			// Check whether all the numbers are in the Galois field.
			if (N[i][j] >= nSize)
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
		}
		delete M;

		for (i = 0; i<nRow2; i++)
		{
			delete[]  N[i];

		}
		delete N;

		return;
	}

	TRACE("\n");

	for (i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			TRACE("%d ", M[i][j]);



		}
		TRACE("\n");
	}

	for (i = 0; i<nRow2; i++)
	{
		for (int j = 0; j<nCol2; j++)
		{
			TRACE("%d ", N[i][j]);

		}
		TRACE("\n");
	}


	/************************************************************************/
	/* Define the Galois filed.                                             */
	/************************************************************************/
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



	if (nOperation == ADD)
	{
		int **R = new int*[nRow];
		for (int j = 0; j<nRow; j++)
		{
			R[j] = new int[nCol];
		}

		for (i = 0; i<nRow; i++)
		{
			for (int j = 0; j<nCol; j++)
			{
				R[i][j] = gf_add(M[i][j], N[i][j]);

			}
		}

		CString m_strValue = (_T(" "));
		for (i = 0; i<nRow; i++)
		{
			for (int j = 0; j<nCol; j++)
			{
				CString strTemp;
				strTemp.Format(_T("%3d "), R[i][j]);
				m_strValue += strTemp;
			}
			m_strValue += "\r\n";
		}
		m_Matrix3.SetWindowText(m_strValue);
		UpdateData(false);

		for (i = 0; i<nRow; i++)
		{
			delete[]  R[i];

		}
		delete R;
	}
	else if (nOperation == MULTIPLY)
	{
		int **R = new int*[nRow];
		for (int j = 0; j<nRow; j++)
		{
			R[j] = new int[nCol2];
		}

		for (i = 0; i<nRow; i++)
		{
			for (int j = 0; j<nCol2; j++)
			{
				int temp = 0;
				for (int z = 0; z<nCol; z++)
				{
					temp = gf_add(temp, gf_mul(M[i][z], N[z][j]));
				}
				R[i][j] = temp;

			}
		}

		CString m_strValue = (_T(" "));
		for (i = 0; i<nRow; i++)
		{
			for (int j = 0; j<nCol2; j++)
			{
				CString strTemp;
				strTemp.Format(_T("%3d "), R[i][j]);
				m_strValue += strTemp;
			}
			m_strValue += "\r\n";
		}
		m_Matrix3.SetWindowText(m_strValue);
		UpdateData(false);


	}


	// Clear memory.
	gf_uninit();

	for (i = 0; i<nRow; i++)
	{
		delete[]  M[i];
	}
	delete M;

	for (i = 0; i<nRow2; i++)
	{
		delete[]  N[i];
	}
	delete N;
}


void CMatrixComputingDlg::OnBnClickedTranspose()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString winText;
	m_Matrix.GetWindowText(winText);
	winText.TrimLeft(_T("\r\n"));
	winText.TrimLeft(_T(" \r\n"));
	winText.TrimRight(_T("\r\n"));
	m_Matrix.SetWindowText(winText);

	int nRow = 0;
	int nCol = 0;

	int i = 0;

	int nInputRow = m_Matrix.GetLineCount();
	char ch[5];
	for (int j = 0; j<nInputRow; j++)
	{
		m_Matrix.GetLine(j, (LPTSTR)ch, 1);

		if (ch[0] != '\r')
		{
			nRow++;
		}
	}												// Now, the number of the row has been obtained.

	CString str;
	m_Matrix.GetWindowText(str);
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

	int **M = new int*[nRow];
	for (int j = 0; j<nRow; j++)
	{
		M[j] = new int[nCol];
	}												// Matrix M has been provided to store all the data.


	bool bError = false;								// if the numbers in the matrix is not the one in the given Galois field, return!
	m_Matrix.GetWindowText(str);
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
			int pos2 = temp.Find(_T(" "));
			if (pos2 != -1)
			{
				CString str = temp.Left(pos2);
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)str);
				M[i][j] = atoi(szTemp);

				M[i][j] = atoi(szTemp);
				int nLen = temp.GetLength();
				temp = temp.Right(nLen - pos2);
				temp.TrimLeft(_T(" "));
			}
			else
			{
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)temp);
				M[i][j] = atoi(szTemp);


			}

		}
		int nLen = str.GetLength();
		str = str.Right(nLen - pos - 2);				//  "\r\n" takes two positions.
	}

	int **MT = new int*[nCol];
	for (int j = 0; j<nCol; j++)
	{
		MT[j] = new int[nRow];
	}

	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nRow; j++)
		{
			MT[i][j] = M[j][i];
		}
	}



	CString m_strValue2 = _T("");
	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nRow; j++)
		{
			CString strTemp;
			strTemp.Format(_T("%3d "), MT[i][j]);
			m_strValue2 += strTemp;
		}
		m_strValue2 += "\r\n";
	}
	m_Matrix3.SetWindowText(m_strValue2);
	UpdateData(false);

	for (i = 0; i<nRow; i++)
	{
		delete[]  M[i];
	}
	delete[] M;

	for (i = 0; i<nCol; i++)
	{
		delete[]  MT[i];
	}
	delete[] MT;
}


void CMatrixComputingDlg::OnBnClickedInverse()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_nOrder > 12)
	{
		return;
	}
	CString winText;
	m_Matrix.GetWindowText(winText);
	winText.TrimLeft(_T(" \r\n"));
	//	winText.TrimLeft("");
	winText.TrimRight(_T("\r\n"));
	m_Matrix.SetWindowText(winText);				// Remove the lines with only a "enter" (namely "\r\n").

	if (winText == "")
	{
		MessageBox(_T("Please input a generator matrix in the following \"EDIT\". You can paste a matrix or input one manually."));
		return;
	}

	int nSize = 2 << (m_nOrder - 1);

	int nRow = 0;
	int nCol = 0;

	int i = 0;

	int nInputRow = m_Matrix.GetLineCount();
	char ch[5];
	for (int j = 0; j<nInputRow; j++)
	{
		m_Matrix.GetLine(j, (LPTSTR)ch, 1);
		if (ch[0] != '\r')
		{
			nRow++;
		}
	}												// Now, the number of the row has been obtained.


	CString str, strTemp;
	m_Matrix.GetWindowText(str);
	int a = 5;
	strTemp = "2";
	strTemp = str;

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
	if (nCol != nRow)
	{
		CString str;
		str.Format(_T("Column=%d, Row=%d. Please input a square matrix.", nCol, nRow));
		MessageBox(str);
		return;
	}

	// Now, we need to define a 2-dimensional array with nRow and nCol specified.

	int **M = new int*[nRow];
	for (int j = 0; j<nRow; j++)
	{
		M[j] = new int[nCol];
	}												// Matrix M has been provided to store all the data.

	int **MCopy = new int*[nRow];
	for (int j = 0; j<nRow; j++)
	{
		MCopy[j] = new int[nCol];
	}

	bool bError = false;								// if the numbers in the matrix is not the one in the given Galois field, return!
	str = strTemp;
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
			int pos2 = temp.Find(_T(" "));
			if (pos2 != -1)
			{
				CString str = temp.Left(pos2);

				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)str);
				M[i][j] = atoi(szTemp);

				M[i][j] = atoi(szTemp);
				int nLen = temp.GetLength();
				temp = temp.Right(nLen - pos2);
				temp.TrimLeft(_T(" "));
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

	TRACE("\n");
	for (i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			MCopy[i][j] = M[i][j];
			TRACE("%d ", M[i][j]);

		}
		TRACE("\n");
	}
	/************************************************************************/
	/* Define the Galois filed.                                             */
	/************************************************************************/
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


	int bRet = Rank((unsigned int **)M, nRow, nCol);

	if (bRet != nRow)
	{
		MessageBox(_T("The matrix is not full-rank. so the inverse matrix can not be obtained!"));
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
	/* Start to get the inverse matrix!                                     */
	/************************************************************************/
	int **N = new int*[nCol];
	for (int j = 0; j<nCol; j++)
	{
		N[j] = new int[2 * nCol];
	}
	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			N[i][j] = M[i][j];
			TRACE("%d\t", N[i][j]);
		}
		for (int j = nCol; j<2 * nCol; j++)
		{
			if (i == j - nCol)
			{
				N[i][j] = 1;
			}
			else
			{
				N[i][j] = 0;
			}
			TRACE("%d\t", N[i][j]);
		}
		TRACE("\n");
	}
	/************************************************************************/
	/* Step 1. Change to a lower triangle matrix.                           */
	/************************************************************************/

	for (i = 0; i<nCol; i++)
	{
		// There must exist a non-zero mainelement.
		TRACE("*********\n");
		if (N[i][i] == 0)
		{
			// Record this line.
			int temp[200] = { 0 };
			for (int k = 0; k<2 * nCol; k++)
			{
				temp[k] = N[i][k];
			}
			// Exchange
			int nRow = nCol;					// They are the same in essensial.
			for (int z = i + 1; z<nRow; z++)
			{
				if (N[z][i] != 0)
				{
					for (int x = 0; x<2 * nCol; x++)
					{
						N[i][x] = N[z][x];
						N[z][x] = temp[x];
					}
					break;
				}
			}

		}


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

	int **CM = new int*[nCol];
	for (int j = 0; j<nCol; j++)
	{
		CM[j] = new int[nCol];
	}
	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			CM[i][j] = N[i][j + nCol];

		}

	}

	CString m_strValue2 = (_T(""));
	for (i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			CString strTemp;
			strTemp.Format(_T("%3d "), CM[i][j]);
			m_strValue2 += strTemp;
		}
		m_strValue2 += "\r\n";
	}
	m_Matrix3.SetWindowText(m_strValue2);
	UpdateData(false);

	// Clean the memory.
	gf_uninit();
	for (i = 0; i<nRow; i++)
	{
		delete[]  M[i];
		delete[]  MCopy[i];
	}
	delete M;
	delete MCopy;

	for (i = 0; i<nCol; i++)
	{
		delete[]  N[i];
		delete[]  CM[i];
	}
	delete N;
	delete CM;
}


void CMatrixComputingDlg::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	nOperation = ADD;
	compute();
}


void CMatrixComputingDlg::OnBnClickedMultiply()
{
	// TODO: Add your control notification handler code here
	nOperation = MULTIPLY;
	compute();
}
unsigned int Rank(GFType **G, GFType nRow, GFType nCol)
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
			//printf("%d\t", *((GFType*)G + nCol*i + j));
			// M[i][j] = *((GFType*)G + nCol*i + j);
			M[i][j] = *(*(G + i) + j);
		}
		// printf("\n");
	}
	// printf("\n");

	for (int i = 0; i<nRow; i++)
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

	for (int i = 0; i<nRow; i++)
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
	for (int i = 1; i<nRow; i++)
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

	int nRank = 0;
	// Get the rank.
	for (int i = 0; i<nRow; i++)
	{
		int nNonzero = 0;
		for (int j = 0; j<nCol; j++)
		{
			if (M[i][j] != 0)
			{
				nNonzero++;
			}

		}
		// If there is only one nonzero element in the new matrix, it is concluded an original packet is leaked. 
		if (nNonzero > 0)
		{
			// Leaked.
			nRank++;
		}
	}



	for (int i = 0; i<nRow; i++)
	{
		delete[]  M[i];
	}
	delete[] M;

	return nRank;
}


void CMatrixComputingDlg::OnEnChangeOrder()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMatrixComputingDlg::OnEnChangeEditleft()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


// SNCcrackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SNCcrack.h"
#include "SNCcrackDlg.h"
#include "afxdialogex.h"
#include "gf.c"
#include <fstream>
#include <iostream>
using namespace std;

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

public:
//	void BruteForce(const  int** G, int nRow, int nCol);
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


// CSNCcrackDlg 对话框



CSNCcrackDlg::CSNCcrackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSNCcrackDlg::IDD, pParent)
	, m_nM(8)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSNCcrackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_M, m_nM);
	DDX_Control(pDX, IDC_EDIT_MATRIX, m_Matrix);
}

BEGIN_MESSAGE_MAP(CSNCcrackDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Read, &CSNCcrackDlg::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_BruteForce, &CSNCcrackDlg::OnBnClickedButtonBruteforce)
END_MESSAGE_MAP()


// CSNCcrackDlg 消息处理程序

BOOL CSNCcrackDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSNCcrackDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSNCcrackDlg::OnPaint()
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
HCURSOR CSNCcrackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSNCcrackDlg::OnBnClickedButtonRead()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, _T("open"), _T("SNCcrack_report.txt"), NULL, NULL, SW_SHOWNORMAL);
}





void CSNCcrackDlg::OnBnClickedButtonBruteforce()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nM > 8 || m_nM < 0){
		MessageBox(_T("Please input 1<m<8."));
		return;
	}
	CString winText;
	m_Matrix.GetWindowText(winText);
	winText.TrimLeft(_T("\r\n"));
	winText.TrimLeft(_T(" \r\n"));
	winText.TrimRight(_T("\t\r\n"));
	m_Matrix.SetWindowText(winText);

	int nSize = (int)pow(2.0, (int)m_nM);

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
	if (nRow > 1)
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
		temp.TrimRight(_T(" \t"));
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


	int **MAT = new int*[nRow];
	int j;
	for (j = 0; j<nRow; j++)
	{
		MAT[j] = new int[nCol];
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
			int pos2 = temp.Find(_T(" "));    //找到数据后面的空格，分离数据
			if (pos2 != -1)
			{
				CString str = temp.Left(pos2);
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)str);
				MAT[i][j] = atoi(szTemp);     //分离数据

				int nLen = temp.GetLength();
				temp = temp.Right(nLen - pos2);//取出一个数据后的剩余部分
				temp.TrimLeft(_T(" \t"));      //去掉前面的空格和制表符
			}
			else
			{
				char szTemp[20] = { 0 };
				//sprintf(szTemp, "%s", temp);
				::wsprintfA(szTemp, "%ls", (LPCTSTR)temp);
				MAT[i][j] = atoi(szTemp);
			}
			if (MAT[i][j] >= nSize)
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
			delete[]  MAT[i];
			
		}

		return;
	}
	remove("SNCcrack_report.txt");
	if (nRow >= nCol){
		ofstream ofile;
		ofile.open("SNCcrack_report.txt");
		ofile << "This is a crack program, when you enter the number of vectors is greater than or equal to "<<nCol<<" , the default use  the former "<<nCol-1 <<" vectors to crack."<< endl;
		ofile.close();
	}
	


	int** matrix;
	int count = (nRow < nCol ? nRow : nCol-1);              
	
	matrix = new int*[count];
	for (i = 0; i < count; i++){
		matrix[i] = new int[nCol];
	}
	for (i = 0; i < count; i++){
		for (j = 0; j < nCol; j++){
			matrix[i][j] = MAT[i][j];
		}
	}
		
	BruteForce(matrix, count, nCol);

    // Release the memory created by "new".
	for (i = 0; i < count; i++){
		delete[]  matrix[i];
	}
	for (i = 0; i<nRow; i++)
	{
		delete[]  MAT[i];
	}
	delete  matrix;
	delete  MAT;
	
}




bool CSNCcrackDlg::BruteForce(int** G, int nRow, int nCol)
{

	int i, j;
	int **M = new int*[nRow];
	for (i = 0; i<nRow; i++)
	{
		M[i] = new int[nCol];
	}

	int **MCopy = new int*[nRow];
	for (i = 0; i<nRow; i++)
	{
		MCopy[i] = new int[nCol];
	}
	// Copy matrix M to Mcopy.

	for (i = 0; i<nRow; i++)                        //把矩阵数据存入ＭCopy
	{
		for (j = 0; j<nCol; j++)
		{
			M[i][j] = G[i][j];
			MCopy[i][j] = G[i][j];
			//TRACE("%d ", M[i][j]);
			//TRACE("\n");
		}
	}

	// Start to crack with the 2-dimensional array.
	// The method we employ to decode an original packet  is to make elementary row transformations.
	// As long as there is one identity vector appeared in the matrix after elementary row transformations. 
	// It is confirmed that the eavesdropper could obtain some meaningful messages with observed given information.

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

	gf_init(m_nM, prim_poly[m_nM]);

	// Now, we know that there are nRow rows, and the coefficient vectors with different order may result in different result.
	// So, the brute force algorithm must traverse all the cases. Therefore, the number of total cases is (nRow!).



	// define an array to identify if the numbers have been selected.
	bool *element = new bool[nRow];

	for (int x = 0; x<nRow; x++)
	{
		element[x] = true;
	}
	bool bLeaked = false;								// Define 


	{
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



			for (j = i + 1; j < nRow; j++)
			{
				// Now, the main element must be nonsingular.

				UINT temp = gf_div(M[j][yPos], M[i][yPos]);
				for (int z = 0; z < nCol; z++)
				{
					M[j][z] = gf_add(M[j][z], gf_mul(temp, M[i][z]));
				}

			}
			// 
			yPos++;

		}


		for (i = 0; i<nRow; i++)
		{
			for (j = 0; j<nCol; j++)
			{
				TRACE("%d ", M[i][j]);
			}
			TRACE("\n");
		}
		TRACE("\n");
		// The matrix becomes a scalar matrix. we need to make more elements become 0 with elementary transformations.
		yPos = 0;
		for (i = 1; i<nRow; i++)
		{
			for (j = 0; j<nCol; j++)
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
				UINT temp = gf_div(M[k][yPos], M[i][yPos]);
				for (int z = 0; z<nCol; z++)
				{
					M[k][z] = gf_add(M[k][z], gf_mul(temp, M[i][z]));
				}
			}
		}



		for (i = 0; i<nRow; i++)
		{
			for (j = 0; j<nCol; j++)
			{
				TRACE("%d ", M[i][j]);
			}
			TRACE("\n");
		}
		TRACE("\n");

		// Check whether there is an identity in the matrix after elementary transformation of matrix. 
		for (i = 0; i<nRow; i++)
		{
			int nNonzero = 0;			//用来记录非零元素个数
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
				MessageBox(_T("Meaningful message is obtained by the eavesdropper."));
				bLeaked = true;
				break;
			}
		}


		if (bLeaked == true)					// Once an original packet is leaked, all the computation must be ended.
		{
			// Generate an report to show that the 

			ofstream ofile;
			ofile.open("SNCcrack_report.txt", ios::out | ios::app);
			ofile << "The original matrix is" << endl;
			
			for (i = 0; i<nRow; i++)
			{
			  for (j = 0; j<nCol; j++)
				{
					ofile<<MCopy[i][j]<<"\t";
				}
			  ofile << endl;
			}
			ofile << endl;

			ofile<<"After elementary transformations of matrix, the new matrix is"<<endl;
			for (i = 0; i<nRow; i++)
			{
				for (j = 0; j<nCol; j++)
				{
					ofile<< M[i][j]<<"\t";
				}
				ofile<<endl;
			}
			ofile<<endl;
			ofile<< "Leaked! From the matrix above, we know that the eavesdropper  could obtain an original packets since there is a row vector in which there is only one nonzero element. And this implies that it is easy to translate the associated data into original data.\n";

			ofile.close();
			for (i = 0; i<nRow; i++)
			{
				delete[]  M[i];
				delete[]  MCopy[i];
			}
			delete M;
			delete MCopy;
			delete element;
     		element = NULL;

			gf_uninit();

			return true;

		}

		// re-initial the original data.
		int x;
		for (x = 0; x<nRow; x++)
		{
			element[x] = true;
		}

	}											// all the cases have been checked.		

	if (bLeaked == false)
	{
		MessageBox(_T("Secure! No meaningful information is leaked."));
		// Generate an report to show that the 

		ofstream ofile;
		ofile.open("SNCcrack_report.txt",ios::out|ios::app);
		ofile << "The original matrix is" << endl;

		for (i = 0; i<nRow; i++)
		{
			for (j = 0; j<nCol; j++)
			{
				ofile << MCopy[i][j] << "\t";
			}
			ofile << endl;
		}
		ofile << endl;

		ofile << "After elementary transformations of matrix, the new matrix is" << endl;
		for (i = 0; i<nRow; i++)
		{
			for (j = 0; j<nCol; j++)
			{
				ofile << M[i][j] << "\t";
			}
			ofile << endl;
		}
		ofile << endl;
		ofile<< "Secure! From the matrix above, we know that the eavesdropper  could  not obtain any original packets since there is no row vector in which there is only one nonzero element. And this implies that the associated data must not be original data.\n";

		ofile.close();
	}

	// Release the memory created by "new".
	for (i = 0; i<nRow; i++)
	{
		delete[] M[i];
		delete[]  MCopy[i];
	}
	delete M;
	delete MCopy;
	delete element;
	element = NULL;

	gf_uninit();
	return false;
}









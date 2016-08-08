
// NetworkCodingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetworkCoding.h"
#include "NetworkCodingDlg.h"
#include "afxdialogex.h"
#include "gf.c"
#include<time.h>

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


// CNetworkCodingDlg 对话框



CNetworkCodingDlg::CNetworkCodingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkCodingDlg::IDD, pParent)
	, K(4)
	, N(6)
	, g_filePath(_T(""))
	
	, Step_info(_T("程序执行步骤\r\n"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_flag = 0;
	g_extName = _T("");
}

void CNetworkCodingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, K);
	DDX_Text(pDX, IDC_EDIT2, N);
	//  DDX_Text(pDX, IDC_Progress, m_szProgress);
	//  DDX_Text(pDX, IDC_Progress, m_szProg);
	DDX_Text(pDX, IDC_Progress, Step_info);
	//  DDX_Control(pDX, IDC_Progress, Scroll);
}

BEGIN_MESSAGE_MAP(CNetworkCodingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Select, &CNetworkCodingDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDC_Code, &CNetworkCodingDlg::OnBnClickedCode)
	ON_BN_CLICKED(IDC_Recovery, &CNetworkCodingDlg::OnBnClickedRecovery)
	ON_BN_CLICKED(IDC_OpenDirectory, &CNetworkCodingDlg::OnBnClickedOpendirectory)
	
	ON_BN_CLICKED(IDC_Clear, &CNetworkCodingDlg::OnBnClickedClear)
	ON_EN_CHANGE(IDC_Progress, &CNetworkCodingDlg::OnEnChangeProgress)
	ON_BN_CLICKED(IDC_Recode, &CNetworkCodingDlg::OnBnClickedRecode)
END_MESSAGE_MAP()


// CNetworkCodingDlg 消息处理程序

BOOL CNetworkCodingDlg::OnInitDialog()
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

void CNetworkCodingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetworkCodingDlg::OnPaint()
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
HCURSOR CNetworkCodingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkCodingDlg::OnBnClickedSelect()
{
	// TODO: Add your control notification handler code here
	Step_info += "23";
	UpdateData(TRUE);
	
	Step_info += "1、开始选择文件";
	Scroll();
	int flag = 0;
	CFileDialog opendlg(TRUE, _T("*"), _T("*"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);//选择文件
	if (opendlg.DoModal() == IDOK)//把文件地址赋给filePath
	{
		g_filePath = opendlg.GetPathName();
		flag = 1;
	}
	if (flag == 0){
		Step_info += "你没有选择文件";
		Scroll();
		return;
	}
	
	USES_CONVERSION;
	char* pfilename = T2A(g_filePath);
	FILE* fp;
	if (fopen_s(&fp, pfilename, "rb")){
		Step_info += "文件打开失败";
		return;
	}
	

	g_flag = 1;    //g_flag全局变量用来控制按钮的点击次序，无序点击会导致程序崩溃
	Step_info += "2、文件选择成功\r\n点击Code按钮开始编码\r\n";
	Step_info += "请输入N，K的值，而且N>K。如果没有输入，将使用默认值N=6，K=4";
	Scroll();
}



void CNetworkCodingDlg::OnBnClickedCode()
{
	// TODO: Add your control notification handler code here

	/************************************************************************/
	/* Step 1. Copy this file to the two-dimensional array.                           */
	/************************************************************************/

	UpdateData(TRUE);
	if (g_flag == 0){
		Step_info += "请点击Select按钮，选择一个文件";
		Scroll();
		return;
	}
	if (N < K||N==K){
		Step_info += "请输入N>K";
		Scroll();
		return;
	}

	
	Step_info += "开始编码文件\r\n1、将文件以二进制方式读入二维数组";
	Scroll();
	

	int i, j;
	
	g_extName = g_filePath.Right(g_filePath.GetLength() - g_filePath.ReverseFind('.') - 1);//获取文件的扩展名
	USES_CONVERSION;
	char* pfilename = T2A(g_filePath);
	FILE* fp;
	if (fopen_s(&fp, pfilename, "rb")){
		MessageBox(_T("File open failed."));
		return;
	}
	fseek(fp, 0, SEEK_END);                              //文件指针移到文件末尾
	long nSize = ftell(fp);                               //获取文件的总长
	long nLen = nSize / K + (nSize % K != 0 ? 1 : 0);     //把文件平均分成K份，每份长度为nLen个字节
	byte* buffer = new byte[K*nLen];

	for (i=0; i<K*nLen; i++)//先把buffer数组置0
	{
		buffer[i] = 0;
	}
	
	fseek(fp, 0, SEEK_SET);     //指向文件开始
	fread(buffer, 1, nSize, fp);//复制文件到buffer数组
	fclose(fp);

	          


	byte** Buf;                                //文件数据存入二维数组中K*nLen
	Buf = new byte*[K];                        //把buffer数组存入二维数组Buf
	for (i = 0; i < K; i++){
		Buf[i] = new byte[nLen];
	}
	byte *p = buffer;            //用来遍历buffer数组
	for (i = 0; i < K; i++){
		for (j = 0; j < nLen; j++){
			Buf[i][j] = *p;
			p++;
		}
	}
	delete[] buffer;
	
	Step_info += "2、获取随机编码矩阵\r\n获得的编码矩阵为";
	Scroll();

	/************************************************************************/
	/* Step 2. Get code matrix(N*K)                                         */
	/************************************************************************/
	byte** codeMatrix;          //编码矩阵N*K
	codeMatrix = new byte*[N];
	for (i = 0; i < N; i++){
		codeMatrix[i] = new byte[K];
	}
	
	CString str;
	for (i = 0; i < N; i++)      //生成随机矩阵
	{
		for (j = 0; j < K; j++)
		{
			codeMatrix[i][j] = rand() % 256;
			str.Format(_T("%-6d"), codeMatrix[i][j]);
			Step_info += str;
		}
		
		Step_info += "\r\n";
	}
	
	Step_info += "3、编码，用编码矩阵乘以读入文件的矩阵";
	Scroll();
	
	

	/************************************************************************/
	/* Step 3. Start Coding                                                 */
	/************************************************************************/
	byte** matrix1;                             //用来存储编码结果N*nLen的矩阵
	matrix1 = Multiply(codeMatrix, Buf, N, K, nLen);
	
	byte** Mat;                             //把编码矩阵与编码结果组成一个矩阵,这是一个N*(1+K+nLen)的矩阵
	Mat = new byte*[N];
	for (i = 0; i < N; i++){
		Mat[i] = new byte[1 + K + nLen];
	}
	for (i = 0; i < N; i++){                   //第0列全为K
		Mat[i][0] = K;
	}
	for (i = 0; i < N; i++){                   //1到K列为编码矩阵codeMatrix
		for (j = 1; j <= K; j++){
			Mat[i][j] = codeMatrix[i][j - 1];
		}
	}
	for (i = 0; i < N; i++){                   //K+1到K+nLen为编码结果
		for (j = K + 1; j <= K + nLen; j++){
			Mat[i][j] = matrix1[i][j - K - 1];
		}
	}
	

	//把矩阵matrix2分开存入N个codeFile文件
	Step_info += "4、把获得的矩阵分开写入N个codeFile文件，编码结束";
	Scroll();

	FILE *fpCd;
	char codeFile[32];
	
	for (i = 1; i <= N; i++)
	{
		_snprintf_s(codeFile, 32, "codeFile%d.", i);//创建文件，为文件命名
		strcat_s(codeFile, T2A(g_extName.GetBuffer()));//把扩展名连接到文件名
		fopen_s(&fpCd,codeFile, "wb");
		fwrite(Mat[i - 1], 1, 1 + K + nLen, fpCd);//写入
		fclose(fpCd);
	}

	
	
	// Clean the memory.
	


	for (i = 0; i<K; i++)
	{
		delete[]  Buf[i];
	}
	delete Buf;

	for (i = 0; i < N; i++){
		delete[] codeMatrix[i];
		delete[] matrix1[i];
		delete[] Mat[i];
	}
	delete codeMatrix;
	delete matrix1;
	delete Mat;

	g_flag = 2;
	Step_info += "点击Open按钮，打开当前工作目录，可以看到N个codefile文件，若是调试模式，文件生成在项目资源目录下\r\n";
	Step_info += "点击Recovery按钮，恢复文件或者点击Recode按钮进行再编码";
	Scroll();
}




byte** CNetworkCodingDlg::Multiply(byte** matA, byte** matB, int nRow, int n, int nCol)
{											//nRow*n的矩阵matA乘以n*nCol的矩阵matB，返回乘积矩阵
	int i, j, k;
	int temp;
	gf_init(8, 0x00000187);                //初始化域
	byte** Mat;                            //用来存储矩阵相乘结果 (nRow*nCol)
	Mat = new byte*[nRow];
	for (i = 0; i < nRow; i++){
		Mat[i] = new byte[nCol];
	}
	for (i = 0; i < nRow; i++){            //两矩阵相乘
		for (j = 0; j < nCol; j++){
			temp = 0;
			for (k = 0; k < n; k++){
				temp = gf_add(temp, gf_mul(matA[i][k], matB[k][j]));
			}
			Mat[i][j] = temp;
		}
	}
	gf_uninit();
	return Mat;
}


void CNetworkCodingDlg::OnBnClickedRecovery()
{
	// TODO: Add your control notification handler code here
	
	
	if (g_flag != 2){
		if (g_flag == 0){
			Step_info += "请点击Select按钮，选择一个文件";
			Scroll();
			return;
		}
		if (g_flag == 3 ){
			Step_info += "编码后的文件已经被删除了，没有文件可供恢复。你可以点击Code按钮重新生成编码文件，也可以重新选择文件";
			Scroll();
			return;
		}
		Step_info += "请点击Code按钮，开始编码";
		Scroll();
		return;
	}


	
	Step_info += "开始解码\r\n1、确定解码获取几个codeFile文件，随机获取用来解码的codeFile文件的序号(codeFile为编码后的文件)";
	Scroll();

	
	int num = 0;             //随机获取用哪个文件来获取解码时需要的文件个数和文件长度    
	num = 1 + rand() % N;
	
	
	int nPart = 0;           //用来存放编码前分成相同大小的文件个数
	long nLength = 0;         //用来存放文件的长度

	FILE *fp;
	USES_CONVERSION;
	char codeFile[32];
	_snprintf_s(codeFile, 32, "codeFile%d.", num);
	strcat_s(codeFile, T2A(g_extName.GetBuffer()));
	fopen_s(&fp, codeFile, "rb");
	fread(&nPart, 1, 1, fp);            //读取需要几个codeFile文件可以恢复数据
	fseek(fp, 0, SEEK_END);
	nLength = ftell(fp);                //读取文件长度
	fclose(fp);

	int i, j;
	int *fileNum = new int[nPart];		//随机获取再编码文件的序号，存入fileNum数组
	for (i = 0; i <nPart; i++){
		fileNum[i] = 1 + rand() % N;
		for (j = 0; j < i; j++){
			if (fileNum[i] == fileNum[j]){
				i--;
				break;
			}
		}
	}

	CString str;
	Step_info += "需要codeFile文件的数量nPart=";
	str.Format(_T("%d"), nPart);
	Step_info += str;
	Scroll();

	Step_info += "解码文件的codeFile文件序号\r\n    ";
	
	for (i = 0; i < nPart; i++){
		str.Format(_T("%-6d"), fileNum[i]);
		Step_info += str;
	}

	Scroll();

	
	
	byte** MAT;                         //用来存放nPart个解码文件，是一个nPart*nLength的矩阵
	MAT = new byte*[nPart];
	for (i = 0; i < nPart; i++){
		MAT[i] = new byte[nLength];
	}


	FILE *fpCd;
	for (i = 0; i < nPart; i++)
	{

		_snprintf_s(codeFile, 32, "codeFile%d.", fileNum[i]);
		strcat_s(codeFile, T2A(g_extName.GetBuffer()));
		fopen_s(&fpCd,codeFile, "rb");
		fread(MAT[i], 1, nLength, fpCd);           //把文件读入数组
		fclose(fpCd);
	}
	
	
	
	//从数组中分离编码矩阵和编码结果


	byte** MAT1;                                     //编码矩阵为nPart*nPart矩阵
	MAT1 = new byte*[nPart];
	for (i = 0; i < nPart; i++){
		MAT1[i] = new byte[nPart];
	}

	for (i = 0; i < nPart; i++){
		for (j = 0; j < nPart; j++){
			MAT1[i][j] = MAT[i][j + 1];
		}
	}
	Step_info += "2、解码。用编码矩阵的逆矩阵乘以编码结果";
	Scroll();

	byte** MAT2;               //编码结果为nPart*(nLength-nPart-1)矩阵
	MAT2 = new byte*[nPart];
	for (i = 0; i < nPart; i++)
	{
		MAT2[i] = new byte[nLength - nPart - 1];
	}
	for (i = 0; i < nPart; i++)
	{
		for (j = 0; j < nLength - nPart - 1; j++)
		{
			MAT2[i][j] = MAT[i][j + 1 + nPart];
		}
	}

	//对编码矩阵求逆
	byte** MAT3;             //编码矩阵的逆矩阵
	MAT3 = Inverse(MAT1, nPart);

	//解码MAT3*MAT2用MAT4来接收结果
	byte** MAT4;
	MAT4 = Multiply(MAT3, MAT2, nPart,nPart , nLength - nPart - 1);

	if (MAT4 == NULL){
		MessageBox(_T("The matrix is not full-rank. so the inverse matrix can not be obtained! This file cannot be recovered."));
		return;
	}
	
	Step_info += "3、把解码结果读入文件，解码结束";
	Scroll();

	//把MAT4写回文件
	FILE* fp1;
	char fileName[32];
	_snprintf_s(fileName, 32, "recovery.");
	strcat_s(fileName, T2A(g_extName.GetBuffer()));
	fopen_s(&fp1,fileName, "wb");
	for (i = 0; i < nPart; i++)
	{
		fwrite(MAT4[i], 1, nLength - nPart - 1, fp1);//写入
	}
	fclose(fp1);

	
	//clear the memory
	for (i = 0; i < nPart; i++){
		delete[] MAT[i];
		delete[] MAT1[i];
		delete[] MAT2[i];
		delete[] MAT3[i];
		delete[] MAT4[i];

	}
	delete[] fileNum;
	delete MAT;
	delete MAT1;
	delete MAT2;
	delete MAT3;
	delete MAT4;
	Step_info += "点击Open按钮，打开当前工作目录，可以看到恢复文件recovery，若是调试模式，文件生成在项目资源目录下\r\n点击Clear按钮，可以清理程序执行过程中生成的文件";
	Scroll();
	

}


byte** CNetworkCodingDlg::Inverse(byte** G, int n)//n为矩阵的维数
{	
	//求秩
	int i;
	int nRow = n;
	int	nCol = n;
	gf_init(8, 0x00000187);
	byte **M = new byte*[nRow];
	for (int j = 0; j<nRow; j++)
	{
		M[j] = new byte[nCol];
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
						byte nVal = M[i][x];
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
			byte temp = gf_div(M[j][yPos], M[i][yPos]);
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
			byte temp = gf_div(M[k][yPos], M[i][yPos]);
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


	//求逆

	int bRet = nRank;

	if (bRet != nRow)
	{

		return NULL;
	}
	/************************************************************************/
	/* Start to get the inverse matrix!                                     */
	/************************************************************************/
	byte **N = new byte*[nCol];
	for (int j = 0; j<nCol; j++)
	{
		N[j] = new byte[2 * nCol];
	}

	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			N[i][j] = G[i][j];
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
			byte temp[200] = { 0 };
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
			byte temp = gf_div(N[j][i], N[i][i]);
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
			byte temp = gf_div(N[k][i], N[i][i]);
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
			byte temp = N[i][i];
			for (int z = 0; z<2 * nCol; z++)
			{
				N[i][z] = gf_div(N[i][z], temp);
			}
		}
	}
	/************************************************************************/
	/* Get the new matrix.                                                  */
	/************************************************************************/

	byte **CM = new byte*[nCol];
	for (int j = 0; j<nCol; j++)
	{
		CM[j] = new byte[nCol];
	}
	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			CM[i][j] = N[i][j + nCol];
		}

	}

	// Clean the memory.
	gf_uninit();


	for (i = 0; i<nCol; i++)
	{
		delete[]  N[i];
	}
	delete N;

	return CM;
}




void CNetworkCodingDlg::OnBnClickedOpendirectory()
{
	// TODO: Add your control notification handler code here
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString PathName(szPath);
	CString PROGRAM_PATH = PathName.Left(PathName.ReverseFind(_T('\\')) + 1);
	ShellExecute(NULL, NULL, _T("explorer"), PROGRAM_PATH, NULL, SW_SHOW);
}





void CNetworkCodingDlg::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	if (g_flag != 2){
		Step_info += "没有程序执行时生成的文件要删除";
		Scroll();
		return;
	}
	int i;
	char fileName[32];
	USES_CONVERSION;
	for (i = 1; i < N + 1; i++)
	{
		_snprintf_s(fileName, 32, "codeFile%d.", i);
		strcat_s(fileName, T2A(g_extName.GetBuffer()));
		remove(fileName);
	}
	_snprintf_s(fileName, 32, "recovery.");
	strcat_s(fileName, T2A(g_extName.GetBuffer()));
	remove(fileName);
	g_flag = 3;
	Step_info += "文件已删除";
	Scroll();
}


void CNetworkCodingDlg::OnEnChangeProgress()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CNetworkCodingDlg::OnBnClickedRecode()
{
	// TODO: Add your control notification handler code here
	
	if (g_flag != 2){
		Step_info += "没有编码后的文件可供再编码,点击Code按钮开始编码";
		Scroll();
		return;
	}
	

	Step_info += "1、开始再编码，随机生成再编码文件的数量，随机选择需要再编码的文件";
	Scroll();


	srand((unsigned)time(NULL));

	int num=0;                    //再编码文件的数量
	num =1 + rand()%N;
	CString str;
	Step_info += "再编码文件的数量num=";
	str.Format(_T("%d"), num);
	Step_info += str;
	Scroll();


	int i, j;
	int *fileNum=new int[N];		//随机获取再编码文件的序号，存入fileNum数组
	for (i = 0; i <num; i++){
		fileNum[i] = 1 + rand() % N;
		for (j = 0; j < i; j++){
				if (fileNum[i] == fileNum[j]){
					i--;
					break;
				}
		}
	}
	
	Step_info += "再编码文件的codeFile文件序号\r\n    ";
   
	char codeFile[32];
	for (i = 0; i < num; i++){
		str.Format(_T("%-6d"),fileNum[i]);
		Step_info += str;
	}

	Scroll();

	Step_info += "2、生成随机的再编码矩阵";
	Scroll();

	byte** reCodeMatrix;                     //生成随机的再编码矩阵
	reCodeMatrix = new byte*[num];
	for (i = 0; i < num; i++){
		reCodeMatrix[i] = new byte[num];
	}
	for (i = 0; i < num; i++)     
	{
		for (j = 0; j < num; j++)
		{
			reCodeMatrix[i][j] = rand() % 256;

		}
	}

	Step_info += "3、从前一次编码后的文件中取出数据放入二维数组";
	Scroll();

	
	FILE *fp;
	                          //取出编码前分成的部分个数

	USES_CONVERSION;
	_snprintf_s(codeFile, 32, "codeFile%d.", fileNum[0]);
	strcat_s(codeFile, T2A(g_extName.GetBuffer()));
	fopen_s(&fp, codeFile, "rb");
	fseek(fp, 0, SEEK_END);
	long length = 0;						
	length = ftell(fp);					  //获取codeFile文件的长度
	fclose(fp);


	byte** Buffer;							//把编码后文件读入数组
	Buffer = new byte*[num];					//Buffer矩阵用于codeFile文件的读入与写回
	for (i = 0; i < num; i++){
		Buffer[i] = new byte[length];
	}

	FILE* fpCd;
	
	for (i = 0; i < num; i++){
		_snprintf_s(codeFile, 32, "codeFile%d.", fileNum[i]);
		strcat_s(codeFile, T2A(g_extName.GetBuffer()));
		fopen_s(&fpCd, codeFile, "rb");
		fread(Buffer[i], 1, length, fpCd);           
		fclose(fpCd);
	}

	
	byte** matrix1;                          //取出编码矩阵和编码后的数据
	matrix1 = new byte*[num];					 //Buffer数组的第0列存的是文件编码前平均分成的个数，这一列不读出	
	for (i = 0; i < num; i++){
		matrix1[i] = new byte[length - 1];
	}
	
	for (i = 0; i < num; i++){
		for (j = 0; j < length-1; j++){
			matrix1[i][j] = Buffer[i][j + 1];
		}
	}

	Step_info += "4、再编码。用再编码矩阵乘以数据矩阵";
	Scroll();

	byte** MAT;									//再编码
	MAT = Multiply(reCodeMatrix, matrix1, num, num, length - 1);



	Step_info += "5、把再编码后的数据重新写回文件，再编码结束";
	Scroll();

	for (i = 0; i < num; i++){                   //把再编码后的数据重新读回数组
		for (j = 1; j < length; j++){
			Buffer[i][j] = MAT[i][j - 1];
		}
	}

	for (i = 0; i < num; i++)                           //把数据写回文件
	{
		_snprintf_s(codeFile, 32, "codeFile%d.", fileNum[i]);
		strcat_s(codeFile, T2A(g_extName.GetBuffer()));
		fopen_s(&fpCd, codeFile, "wb");
		fwrite(Buffer[i], 1, length, fpCd);       //写入
		fclose(fpCd);
	}

	for(i = 0; i < num; i++){
		delete[] reCodeMatrix[i];
		delete[] Buffer[i];
		delete[] matrix1[i];
		delete[] MAT[i];
	}
	delete[] fileNum;
	delete reCodeMatrix;
	delete Buffer;
	delete matrix1;
	delete MAT;
	Step_info += "点击Recovery按钮，恢复文件";
	Scroll();
}





void CNetworkCodingDlg::Scroll()//把edit control滚动到最后一行
{
	Step_info += "\r\n";
	UpdateData(FALSE);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_Progress);
	pedit->LineScroll(pedit->GetLineCount());
}

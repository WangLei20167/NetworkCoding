// SRNC_ConstructorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SRNC_Constructor.h"
#include "SRNC_ConstructorDlg.h"
#include "Node.h"
#include "Link.h"
#include <math.h>
#include "FordFulkson.h"
#include "gf.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

unsigned int Rank(GFType **G, GFType nRow, GFType nCol);

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
// CSRNC_ConstructorDlg dialog

CSRNC_ConstructorDlg::CSRNC_ConstructorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSRNC_ConstructorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSRNC_ConstructorDlg)
	m_strOutput = _T("");
	m_bShowLinkNo = FALSE;
	m_bShowNodeNo = FALSE;
	m_nAlgorithm = -1;
	m_strGCV = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nMulticastCapacity = 0;
}

void CSRNC_ConstructorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSRNC_ConstructorDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strOutput);
	DDX_Check(pDX, IDC_CHECK_LinkNum, m_bShowLinkNo);
	DDX_Check(pDX, IDC_CHECK_NodeNum, m_bShowNodeNo);
	DDX_Radio(pDX, IDC_RADIO_algorithm, m_nAlgorithm);
	DDX_Text(pDX, IDC_STATIC_GCV, m_strGCV);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSRNC_ConstructorDlg, CDialog)
//{{AFX_MSG_MAP(CSRNC_ConstructorDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_ImportTopo, OnBUTTONImportTopo)
ON_BN_CLICKED(IDC_BUTTON_Maxflow, OnBUTTONMaxflow)
ON_BN_CLICKED(IDC_BUTTON_AssignCode, OnBUTTONAssignCode)
ON_BN_CLICKED(IDC_CHECK_LinkNum, OnCHECKLinkNum)
ON_BN_CLICKED(IDC_CHECK_NodeNum, OnCHECKNodeNum)
ON_BN_CLICKED(IDC_RADIO_algorithm, OnRADIOalgorithm)
ON_BN_CLICKED(IDC_RADIO_Dalgorithm, OnRADIODalgorithm)
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BUTTON_Check, OnBUTTONCheck)
ON_WM_DESTROY()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRNC_ConstructorDlg message handlers

BOOL CSRNC_ConstructorDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	m_bShowNodeNo = TRUE;
	m_bShowLinkNo = true;
	m_nAlgorithm = 0;
	m_nOrder = 0;
	
	
	GetDlgItem(IDC_BUTTON_Maxflow)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AssignCode)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Check)->EnableWindow(FALSE);
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSRNC_ConstructorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSRNC_ConstructorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
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
	
	CWnd *pWnd=GetDlgItem(IDC_STATIC1);  
    CDC *pControlDC=pWnd->GetDC();      
	pWnd->Invalidate();    
	pWnd->UpdateWindow();
	
	POSITION posLink;	
	posLink = m_linkList.GetHeadPosition();
	CLink *pLink;
	CPen pen1, pen2, pen3, pen4;
	CPen *oldPen;
	pen1.CreatePen(PS_SOLID,2,RGB(192,0,0));
	pen2.CreatePen(PS_DASH,1,RGB(0,0,0)); 
	pen3.CreatePen(PS_SOLID,1,RGB(255,64,64)); 
	pen4.CreatePen(PS_SOLID,2,RGB(255,64,64));
	
	while (posLink != NULL)
	{
		pLink = (CLink *)m_linkList.GetAt(posLink);
		
		if (pLink->bSel == TRUE)
		{
			
			pControlDC->SelectObject(&pen1);			
		}
		else
		{
			pControlDC->SelectObject(&pen2);
			/*			if (pLink->nShared%2 == 0)
			{
			pControlDC->SelectObject(&pen2);
			}
			else if (pLink->nShared%2 == 1)
			{
			pControlDC->SelectObject(&pen3);
			}
			*/			
			if (pLink->bInSubGraph == TRUE)
			{
				if (pLink->nInputLink >= 2)
				{
					pControlDC->SelectObject(&pen4);		
					for (int k=0; k<pLink->nInputLink; k++)
					{
						TRACE("%d  ", pLink->nPreLink[k]);
					}
					TRACE("\n");
				}
				else
				{
					pControlDC->SelectObject(&pen3);
				}		
			}
			else
			{
				pControlDC->SelectObject(&pen2);
			}
		}
		int xpos = (pLink->posStartPos.x+pLink->posEndPos.x)/2.0 - 5;
		int ypos = (pLink->posStartPos.y+pLink->posEndPos.y)/2.0 - 5;
		CString strNo;
		strNo.Format("%d", pLink->nLinkNum);
		
		CFont font,*pOldFont;
		font.CreateFont(10, 6,20,0, 700,TRUE,FALSE,TRUE, ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
		pOldFont=pControlDC->SelectObject(&font);
		
		pControlDC->SetTextColor(RGB(0, 0, 255));
		pControlDC->SetBkMode(TRANSPARENT); 
		if (m_bShowLinkNo)
		{
			pControlDC->TextOut(xpos, ypos, strNo);
		}
		
		pControlDC->SelectObject(pOldFont);
		pControlDC->MoveTo(pLink->posStartPos);
		pControlDC->LineTo(pLink->posEndPos);
		
		// Add a small arrow
		DrawArrow(pControlDC, pLink->posStartPos, pLink->posEndPos, 15, 10);
		
		m_linkList.GetNext(posLink);
	}
	
	pControlDC->SelectObject(&pen2);
	
	
	CBrush *pBrushRed = new CBrush(RGB(255, 0, 0));
	CBrush *pBrushBlue = new CBrush(RGB(0, 0, 255));
	CBrush *pBrushGreen = new CBrush(RGB(0, 255, 0));
	CBrush *pBrushDecode = new CBrush(RGB(0, 255, 255));
	
	POSITION pos;	
	pos = m_nodeList.GetHeadPosition();
	CNode *myNode;
	while (pos != NULL)
	{
		myNode = (CNode *)m_nodeList.GetAt(pos);
		CBrush *pBrush;
		if (myNode->strType == "Source")
		{
			pBrush = pBrushRed;
		}
		else if (myNode->strType == "Relay")
		{
			pBrush= pBrushBlue;
		}
		else if (myNode->strType == "Sink")
		{
			pBrush = pBrushGreen;
			if (myNode->bDecodable == true)
			{
				pBrush = pBrushDecode;
			}
			
		}	
		
		pControlDC->SelectObject(pBrush);
		int nSize = 5;
		pControlDC->Ellipse(myNode->nXPos-nSize, myNode->nYPos-nSize,myNode->nXPos+nSize, myNode->nYPos+nSize);
		
		// Draw the number of the node
		int xPos = myNode->nXPos+5;
		int yPos = myNode->nYPos-10;
		CString strID;
		strID.Format("%d", myNode->nNodeID);
		CFont font,*pOldFont;
		font.CreateFont(10, 6,20,0, 700,TRUE,FALSE,TRUE, ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
		pOldFont=pControlDC->SelectObject(&font);
		pControlDC->SetTextColor(RGB(255,0,0));
		if (m_bShowNodeNo)
		{
			pControlDC->TextOut(xPos, yPos, strID);
		}
		
		m_nodeList.GetNext(pos);
	}
	
	
	delete pBrushDecode;
	delete pBrushGreen;
	delete pBrushRed;
	delete pBrushBlue;
	
	pWnd->ReleaseDC(pControlDC);
	
	// Fix the scrollbar at the bottom of the Edit.
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->SetSel(-1);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSRNC_ConstructorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSRNC_ConstructorDlg::OnBUTTONImportTopo() 
{
	// TODO: Add your control notification handler code here
	
	
	UpdateData(TRUE);
	CString strFileName;
	
	char szFilter[] = "Topology files(*.topo)|*.topo";
	CFileDialog dlg(1, NULL, NULL, NULL, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetPathName();	
	}
	else
	{
		return;
	}
	// MessageBox(strFileName);
	
	m_nodeList.RemoveAll();
	m_linkList.RemoveAll();
	
	int nNodeNum = 0;
	int nLinkNum = 0;
	FILE *pFile = NULL;
	pFile = fopen(LPCTSTR(strFileName),"r");
	CHAR str[100], linkType[100];
	fscanf(pFile, "%d %d", &nNodeNum, &nLinkNum);
	fscanf(pFile, "%s", str);
	
	CString strType;
	int xPos = 0;
	int yPos = 0;
	for (int i=0; i<nNodeNum; i++)
	{
		fscanf(pFile, "%s %d %d", str, &xPos, &yPos);
		CNode* pNode = new CNode;
		pNode->strType.Format("%s", str);
		pNode->nXPos = xPos;
		pNode->nYPos = yPos;
		pNode->nNodeID = i+1;
		m_nodeList.AddTail((CObject *)pNode);
	}
	// Jump the two lines in the topology file.
	
	//	fscanf(pFile, "%s", str);
	//	fscanf(pFile, "%s", str);
	//	fscanf(pFile, "%s", str);
	
	fgets(str, 90, pFile);
	fgets(str, 90, pFile);
	fgets(str, 90, pFile);
	
	int nStartX = 0;
	int nStartY = 0;
	int nEndX = 0;
	int nEndY = 0;
	
	for (i=0; i<nLinkNum; i++)
	{
		fscanf(pFile, "%s %d %d %d %d", linkType, &nStartX, &nStartY, &nEndX, &nEndY);
		CLink* pLink = new CLink;
		pLink->nLinkNum = i+1;
		pLink->posStartPos.x = nStartX;
		pLink->posStartPos.y = nStartY;
		pLink->posEndPos.x = nEndX;
		pLink->posEndPos.y = nEndY;
		
		m_linkList.AddTail((CObject *)pLink);
	}
	
	fclose(pFile);
	
	m_strOutput = "";
	UpdateData(FALSE);
	
	
	GetDlgItem(IDC_BUTTON_Maxflow)->EnableWindow(true);
	
	InvalidateRect(false);
}

void CSRNC_ConstructorDlg::DrawArrow(CDC *pControlDC, CPoint p1, CPoint p2, double theta, int length)
{
	theta=3.1415926*theta/180; 
	double Px,Py,P1x,P1y,P2x,P2y;
	
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	
	P1x=Px*cos(theta)-Py*sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;
	
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	
	// 	CPen pen,pen1,*oldpen;
	// 	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	// 	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	// 	oldpen=dc.SelectObject(&pen);
	pControlDC->MoveTo(p1.x,p1.y);
	pControlDC->LineTo(p2.x,p2.y);
	// 	dc.SelectObject(&pen1);
	pControlDC->MoveTo(p2.x,p2.y);
	pControlDC->LineTo(P1x,P1y);
	pControlDC->MoveTo(p2.x,p2.y);
	pControlDC->LineTo(P2x,P2y);
	// 	dc.SelectObject(oldpen);
}

void CSRNC_ConstructorDlg::OnBUTTONMaxflow() 
{
	// TODO: Add your control notification handler code here
	m_strOutput = "";
	m_nMulticastCapacity = 0;
	int N = m_nodeList.GetCount();
	
	// Define a Ford-Fulkerson object.
	CFordFulkson ff;
	ff.nNodeNum = N;
	ff.Initialize();
	
	// 
	int **Graph = new int*[N];
	for(int i=0; i < N; i++)
		Graph[i] = new int[N];
	
	// Initialize
	for (i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			Graph[i][j] = 0;
		}
	}
	
	POSITION posLink;
	posLink = m_linkList.GetHeadPosition();
	CLink *pLink;
	while (posLink != NULL)
	{
		pLink = (CLink *)m_linkList.GetAt(posLink);
		
		POSITION pos;
		pos = m_nodeList.GetHeadPosition();
		CNode *pNode;
		while (pos != NULL)
		{
			pNode = (CNode*)m_nodeList.GetAt(pos);
			CPoint nodePos;
			nodePos.x = pNode->nXPos;
			nodePos.y = pNode->nYPos;
			
			if (nodePos == pLink->posStartPos)
			{
				pLink->nStartAt = pNode->nNodeID;
				break;
			}
			else
			{
				m_nodeList.GetNext(pos);
			}
			
		}
		
		pos = m_nodeList.GetHeadPosition();
		while (pos != NULL)
		{
			pNode = (CNode*)m_nodeList.GetAt(pos);
			CPoint nodePos;
			nodePos.x = pNode->nXPos;
			nodePos.y = pNode->nYPos;
			
			if (nodePos == pLink->posEndPos)
			{
				pLink->nEndAt = pNode->nNodeID;
				break;
			}
			else
			{
				m_nodeList.GetNext(pos);
			}
			
		}
		m_linkList.GetNext(posLink);
		
	}
	
	posLink = m_linkList.GetHeadPosition();
	
	while (posLink != NULL)
	{
		pLink = (CLink *)m_linkList.GetAt(posLink);
		Graph[pLink->nStartAt-1][pLink->nEndAt-1] = 1;
		
		m_linkList.GetNext(posLink);
	}
	
	CString myStr = "The Graph matrix is \r\n";
	m_strOutput += myStr;
	
	for (i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			// TRACE("%d ", Graph[i][j]);
			CString str;
			str.Format("%d  ", Graph[i][j]);
			m_strOutput = m_strOutput+str;
			
			ff.C[i][j] = Graph[i][j];
		}
		m_strOutput = m_strOutput+"\r\n";
	}
	
	m_strOutput = m_strOutput+"\r\n";
	UpdateData(FALSE);
	
	// Get the ID of the source node and the dest node.
	POSITION pos = m_nodeList.GetHeadPosition();
	while (pos != NULL)
	{
		CNode* pNode = (CNode*)m_nodeList.GetAt(pos);
		
		if (pNode->strType == "Source")
		{
			ff.nSrc = pNode->nNodeID;
			m_nSrcID = pNode->nNodeID;
			break;
		}
		else
		{
			m_nodeList.GetNext(pos);
		}
	}
	
	pos = m_nodeList.GetHeadPosition();
	while (pos != NULL)
	{
		CNode* pNode = (CNode*)m_nodeList.GetAt(pos);
		
		if (pNode->strType == "Sink")
		{
			ff.nDes = pNode->nNodeID;
			
			for (i=0; i<N; i++)
			{
				for (int j=0; j<N; j++)
				{
					// TRACE("%d ", Graph[i][j]);
					
					ff.C[i][j] = Graph[i][j];
				}
				
			}
			for (i=0; i<20; i++)
			{
				for (int j=0; j<20; j++)
				{
					ff.Route[i][j] = -1;
				}
			}
			
			ff.pLinkList = &m_linkList;
			
			int nRet = ff.RunFF();
			CString str;
			str.Format("Maxflow to Node %d is %d.\r\n", pNode->nNodeID, nRet);
			m_strOutput += str;
			pNode->nMaxflow = nRet;
			pNode->nOriginalMaxflow = nRet;
			
			if (m_nMulticastCapacity == 0)
			{
				m_nMulticastCapacity = nRet;
			}
			else
			{
				if (nRet < m_nMulticastCapacity)
				{
					m_nMulticastCapacity = nRet;
				}
			}
			m_strOutput += "The routes from source to this node are:\r\n";
			// Copy the route 
			for (i = 0; i<20; i++)
			{
				if (ff.Route[i][0] == -1)
				{
					break;
				}
				CString str;
				for (int j=0; j<20; j++)
				{
					pNode->nRoutes[i][j] = ff.Route[i][j];
					if (pNode->nRoutes[i][j] != -1)
					{
						TRACE("%d ", pNode->nRoutes[i][j]);
						str.Format("%d ", pNode->nRoutes[i][j]);
						m_strOutput += str;
					}
					else
					{
						TRACE("\n");
						m_strOutput += "\r\n";
						break;
					}
				}
			}
			m_strOutput += "\r\n";
			TRACE("\n*****\n");
			
			m_nodeList.GetNext(pos);
		}
		else
		{
			m_nodeList.GetNext(pos);
		}
	}
	// Now we have obtain the multicast_capacity.
	CString str;
	str.Format("The multicast capacity is %d.\r\n", m_nMulticastCapacity);
	m_strOutput += str;
	
	str.Format("Therefore, all the sink nodes should receive at this rate.\r\n");
	m_strOutput += str;
	
	
	for(i = 0; i < N; i++) 
	{
		delete []Graph[i];
	}
	delete []Graph; 

	GetDlgItem(IDC_BUTTON_Maxflow)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AssignCode)->EnableWindow(true);

	UpdateData(FALSE);
	InvalidateRect(FALSE);	
	
}

void CSRNC_ConstructorDlg::OnBUTTONAssignCode() 
{
	// TODO: Add your control notification handler code here
	
	
	/************************************************************************/
	/*    Start to assign network codes.                                    */
	/************************************************************************/
	
	// Includes the code required by the Galois library.
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
	
	
	// Since the max-flow for each sink node may be different, so we only select m_nMulticastCapacity shortest routes for each sink node so that the energ efficiency can be increased.
	
	// Reset nInputlink and nPrelink array.
	POSITION posLink = m_linkList.GetHeadPosition();
	while (posLink != NULL)
	{
		CLink* pLink = (CLink*)m_linkList.GetAt(posLink);
		for (int z=0; z<pLink->nInputLink; z++)
		{
			pLink->nPreLink[z] = -1;
		}
		pLink->nInputLink = 0;
		pLink->bInSubGraph = FALSE;
		
		m_linkList.GetNext(posLink);
	}
	
	POSITION pos = m_nodeList.GetHeadPosition();
	while (pos != NULL)
	{
		CNode* pNode = (CNode*)m_nodeList.GetAt(pos);
		if (pNode->strType == "Sink")
		{
			
			int nDimension = m_nMulticastCapacity;
			int pRouteHop[30];
			for (int c=0; c<30; c++)
			{
				pRouteHop[c] = -1;
			}
			// Init
			for (int i=0; i<pNode->nMaxflow; i++)
			{
				pRouteHop[i] = 0;
			}
			
			for (i=0; i<pNode->nMaxflow; i++)
			{
				for (int j=0; j< 30; j++)
				{
					if (pNode->nRoutes[i][j] == -1)
					{
						break;
					}
					else
					{
						pRouteHop[i]++;
					}
				}
			}
			int nTempRoutes[30][30];
			for (i=0; i<30; i++)
			{
				for (int j=0; j<30; j++)
				{
					nTempRoutes[i][j] = -1;
				}
			}
			
			for (i=0; i<nDimension; i++)		// nDimension = m_nMulticastCapacity
			{
				int nTemp = 100;
				int nPos = -1;
				for (int j=0; j<pNode->nMaxflow; j++)
				{
					if (pRouteHop[j] < nTemp)
					{
						nTemp = pRouteHop[j];
						nPos = j;
						
					}
				}
				pRouteHop[nPos] = 100;
				
				// Find the row number of the routes with minimal hops.
				
				for (int k=0; k<30; k++)
				{
					nTempRoutes[i][k] = pNode->nRoutes[nPos][k];
				}
				
			}
			
			CString str;
			// Copy nTempRoutes to pNode->nRoutes
			// 			m_strOutput += "*******\r\n";
			
			
			str.Format("Sink %d selects %d shortest routes.\r\n", pNode->nNodeID, m_nMulticastCapacity);
			m_strOutput += str;
			for (i=0; i<nDimension; i++)
			{
				for (int j=0; j<30; j++)
				{
					
					pNode->nRoutes[i][j] = nTempRoutes[i][j];
					// 					str.Format("%d ", pNode->nRoutes[i][j]);
					// 					m_strOutput += str;
					
				}
				// 				m_strOutput += "\r\n";
				
			}
			for (i=0; i<nDimension; i++)
			{
				for (int j=0; j<30; j++)
				{
					if (nTempRoutes[i][j] != -1)
					{
						str.Format("%d ", pNode->nRoutes[i][j]);
						m_strOutput += str;
					}
					
				}
				m_strOutput += "\r\n";		
				
			}
			pNode->nMaxflow = m_nMulticastCapacity;
			
			for (int m=0; m<m_nMulticastCapacity; m++)
			{
				for (int n=30-1; n>=0; n--)
				{
					if (pNode->nRoutes[m][n] != -1)
					{
						POSITION linkFind = m_linkList.GetHeadPosition();
						while (linkFind != NULL)
						{
							CLink* pLink = (CLink*)m_linkList.GetAt(linkFind);
							if (pLink->nLinkNum == pNode->nRoutes[m][n])
							{
								if (n != 0)
								{
									// Find this link in its memory
									bool bFind = FALSE;
									for (int x=0; x<pLink->nInputLink; x++)
									{
										if (pLink->nPreLink[x] == pNode->nRoutes[m][n-1])
										{
											bFind = TRUE;
											break;
										}
									}
									if (bFind == FALSE)
									{
										pLink->nPreLink[pLink->nInputLink] = pNode->nRoutes[m][n-1];
										pLink->nInputLink++;
									}
								}
								else
								{
									pLink->nInputLink = 1;
								}
								
								pLink->bInSubGraph = TRUE;
								
								break;
							}
							m_linkList.GetNext(linkFind);
						}
					}
				}
				
			}
			
			
		}
		
		
		m_nodeList.GetNext(pos);
	}
	
	
	
	
	
	
	// Code assignment when using random algorithm at intermediate nodes
	if (m_nAlgorithm == 0)
	{
		int nOrder = 8;
		m_nOrder = nOrder;
		gf_init(nOrder, prim_poly[nOrder]);
		int nLinkAssignedCnt = 0;
		
		UsingRandomAlgorithm();
		
		CString str = "Global encoding vector for each link has been assigned. Single-click each link to see the coding vector.\r\n";
		m_strGCV = str;
		m_strOutput += str;
		
		m_strOutput += "The used finite field is GF(256) due to the random algorithm.\r\n";
		
		gf_uninit();
		
	}
	else if (m_nAlgorithm == 1)			
	{
		UsingDeterministicAlgorithm();
		
		CString str = "Global encoding vector for each link has been assigned. Single-click each link to see the coding vector.\r\n";
		m_strGCV = str;
		m_strOutput += str;
		
		CString mystr;
		mystr.Format("%d", 1<<m_nOrder);
		m_strOutput = m_strOutput+"The used finite field is GF("+mystr+") due to the deterministic algorithm.\r\n";
		
		
		
	}
	
	GetDlgItem(IDC_BUTTON_AssignCode)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Check)->EnableWindow(true);
	
	UpdateData(false);
	InvalidateRect(false);
	
}

void CSRNC_ConstructorDlg::OnCHECKLinkNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	Invalidate(FALSE);
}

void CSRNC_ConstructorDlg::OnCHECKNodeNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	Invalidate(FALSE);
}

void CSRNC_ConstructorDlg::OnRADIOalgorithm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	
}

void CSRNC_ConstructorDlg::OnRADIODalgorithm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	
}

void CSRNC_ConstructorDlg::UsingRandomAlgorithm()
{
	/************************************************************************/
	/* Assign Network Codes in a topological order.                         */
	/************************************************************************/
	srand(time(NULL)); 
	// Assign for those outgoing link of the source node.
	POSITION pos = m_linkList.GetHeadPosition();
	while (pos != NULL)
	{
		CLink* pLink = (CLink*)m_linkList.GetAt(pos);
		
		if (pLink->nStartAt == m_nSrcID && pLink->bAssigned == FALSE)
		{
			for (int i=0; i<m_nMulticastCapacity; i++)
			{
				pLink->GCV[i] = rand()%(256);		// 随机算法时，默认GF(256)
			}
			pLink->bAssigned = TRUE;
		}
		
		m_linkList.GetNext(pos);
	}
	
	
	while (1)
	{	
		bool bBreak = TRUE;
		
		// Endless loop until all the links being assigned GEVs
		pos = m_linkList.GetHeadPosition();
		while (pos != NULL)
		{
			CLink* pLink = (CLink*)m_linkList.GetAt(pos);
			int nDimension = m_nMulticastCapacity;
			if (pLink->nStartAt != m_nSrcID && pLink->bAssigned == false)
			{
				// For each link, the input link number must be no less than 1.
				if (pLink->nInputLink == 1)
				{
					if (PreLinkAssigned(pLink->nPreLink[0]) == TRUE)
					{
						// copy the GCV
						for (int z=0; z<nDimension; z++)
						{
							pLink->GCV[z] = m_pPreLink->GCV[z];
						}
						pLink->LCV[0] = 1;								// 1 input, the LOC must be 1.
						pLink->bAssigned = TRUE;
					}
					else
					{
						bBreak = false;   // The previous link is not assigned, so the loop can not stop.
					}
				}
				else
				{
					int nPre = pLink->nInputLink;
					bool bAllPreAssigned = TRUE;
					for (int j=0; j<nPre; j++)
					{
						if (PreLinkAssigned(pLink->nPreLink[j]) == FALSE)
						{
							bAllPreAssigned = FALSE;
						}
						else
						{
							bBreak = false;   // The previous link is not assigned, so the loop can not stop.
						}
					}
					if (bAllPreAssigned == TRUE)
					{
						int tempGCV[20] = {-1};
						
						for (int j=0; j<nPre; j++)
						{
							int nNum = pLink->nPreLink[j];
							int nCoeff = 0;
							nCoeff = rand()%(256);
							if (PreLinkAssigned(pLink->nPreLink[j]) == TRUE)
							{
								// copy the GCV
								for (int z=0; z<nDimension; z++)
								{
									if (tempGCV[z] == -1 && m_pPreLink->GCV[z] == -1 )
									{
										tempGCV[z] = -1;
									}
									else if (tempGCV[z] == -1 && m_pPreLink->GCV[z] != -1)
									{
										tempGCV[z] = gf_mul(nCoeff, m_pPreLink->GCV[z]);
									}
									else if (tempGCV[z] != -1 && m_pPreLink->GCV[z] == -1)
									{
										tempGCV[z] = tempGCV[z];
									}
									else if (tempGCV[z] != -1 && m_pPreLink->GCV[z] != -1)
									{
										// Obtain a randomized number in the field.						
										tempGCV[z] = gf_add(tempGCV[z], gf_mul(nCoeff, m_pPreLink->GCV[z]));
									}
									
								}
								
							}
							
							pLink->LCV[j] = nCoeff;
							
						}
						// copy the GCV
						for (int z=0; z<nDimension; z++)
						{
							pLink->GCV[z] = tempGCV[z];
						}
						
						pLink->bAssigned = TRUE;
					}
				}
			}
			
			m_linkList.GetNext(pos);
		}
		
		if (bBreak == TRUE)
		{
			break;
		}
		}
		
}


bool CSRNC_ConstructorDlg::PreLinkAssigned(int nLinkNum)
{
	POSITION posSearch = m_linkList.GetHeadPosition();
	while (posSearch != NULL)
	{
		CLink* pLinkSearch = (CLink*)m_linkList.GetAt(posSearch);
		if (pLinkSearch->nLinkNum == nLinkNum && pLinkSearch->bAssigned == TRUE)
		{
			m_pPreLink = pLinkSearch;
			return TRUE;
		}
		m_linkList.GetNext(posSearch);
	}
	m_pPreLink = NULL;
	return false;
}

void CSRNC_ConstructorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRect lpRec; 
	GetDlgItem(IDC_STATIC1)->GetWindowRect(&lpRec); 
	ScreenToClient(&lpRec);
	
	int x1 = point.x - lpRec.left;
	int y1 = point.y - lpRec.top;
	
	POSITION posLink;
	CLink *pLink;
	posLink = m_linkList.GetHeadPosition();
	/*	while (posLink != NULL)
	{
	pLink = (CLink *)m_linkList.GetAt(posLink);
	pLink->bSel = FALSE;
	m_linkList.GetNext(posLink);
	}
	*/
	posLink = m_linkList.GetHeadPosition();
	
	while (posLink != NULL)
	{
		pLink = (CLink *)m_linkList.GetAt(posLink);
		
		int nXBig = 0;
		int nYBig = 0;
		int nXSmall = 0;
		int nYSmall = 0;
		
		if (pLink->posStartPos.x > pLink->posEndPos.x)
		{
			nXBig = pLink->posStartPos.x;
			nXSmall = pLink->posEndPos.x;
		}
		else
		{
			nXSmall = pLink->posStartPos.x;
			nXBig = pLink->posEndPos.x;
		}
		
		if (pLink->posStartPos.y > pLink->posEndPos.y)
		{
			nYBig = pLink->posStartPos.y;
			nYSmall = pLink->posEndPos.y;
		}
		else
		{
			nYSmall = pLink->posStartPos.y;
			nYBig = pLink->posEndPos.y;
		}
		
		
		if (x1>nXSmall&&x1<nXBig || y1<nYBig&&y1>nYSmall)
		{
			double a = pLink->posEndPos.y - pLink->posStartPos.y;
			double b = pLink->posStartPos.x - pLink->posEndPos.x;
			double c = (pLink->posEndPos.x * pLink->posStartPos.y) - (pLink->posStartPos.x * pLink->posEndPos.y);
			double h = abs(a*x1 + b* y1 + c)/sqrt(a*a + b*b);
			
			if (h <= 5)
			{
				//pLink->bSel = TRUE;
				pLink->bSel = !pLink->bSel;
				// Show the GCV.
				int i=0;
				CString str, strTemp;
				str.Format("LinkID:%d, global encoding vector is ", pLink->nLinkNum);
				while(pLink->GCV[i] != -1)
				{
					strTemp.Format("%d ", pLink->GCV[i]);
					str += strTemp;
					i++;
				}
				str += "Local encoding vector is ";
				int n = pLink->nInputLink;
				for (i=0; i<n; i++)
				{
					strTemp.Format("%d ", pLink->LCV[i]);
					str += strTemp;
				}
				str+=" for link (";
				for (i=0; i<n; i++)
				{
					strTemp.Format("%d ", pLink->nPreLink[i]);
					str += strTemp;
				}
				str +=").";
				m_strGCV = str;
				GetDlgItem(IDC_STATIC_GCV)->SetWindowText(str);
				InvalidateRect(false);
				break;
			}
		}
		
		m_linkList.GetNext(posLink);
		
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CSRNC_ConstructorDlg::OnBUTTONCheck() 
{
	// TODO: Add your control notification handler code here
	
	gf_init(m_nOrder, prim_poly[m_nOrder]);
	POSITION pos = m_nodeList.GetHeadPosition();
	while (pos != NULL)
	{
		CNode* pNode = (CNode*)m_nodeList.GetAt(pos);
		
		if (pNode->strType == "Sink")
		{
			int N = m_nMulticastCapacity;
			// Dynamically construct a N*N Receiving Matrix (RM).
			UINT **RM = new UINT*[N];		
			for(int i=0; i < N; i++)
				RM[i] = new UINT[N];
			// Initialize the RM with 0.
			for (i=0; i<N; i++)
			{
				for (int j=0; j<N; j++)
				{
					RM[i][j] = 0;
				}
			}
			int nCurPos = 0;
			
			POSITION posLink = m_linkList.GetHeadPosition();
			while (posLink != NULL)
			{
				CLink* pLink = (CLink*)m_linkList.GetAt(posLink);
				if (pLink->nEndAt == pNode->nNodeID && pLink->bInSubGraph == TRUE)
				{
					for (int k=0; k<N; k++)
					{
						RM[nCurPos][k] = pLink->GCV[k];
					}
					nCurPos++;
				}
				if (nCurPos == N)
				{
					break;
				}
				
				m_linkList.GetNext(posLink);
			}
			
			CString str, str2;;
			str.Format("Receiving matrix of node %d is\r\n", pNode->nNodeID);
			for (i=0; i<N; i++)
			{
				for (int j=0; j<N; j++)
				{
					str2.Format("%d\t", RM[i][j]);
					str += str2;
				}
				str += "\r\n";
			}
			m_strOutput += str;
			
			// check whether RM is full rank
			int nRank = Rank(RM, N, N);
			if (nRank == N)
			{
				str.Format("Full rank, so this receiver could successfully decode.\r\n");
				m_strOutput+=str;
			}
			
			m_strOutput += "\r\n";
			// Release memeory
			for( i = 0; i < N; i++) 
			{
				delete []RM[i];
			}
			delete []RM; 
		}
		
		m_nodeList.GetNext(pos);
	}
	
	gf_uninit();
	
	GetDlgItem(IDC_BUTTON_Check)->EnableWindow(false);
	
	int nTotalRate = 0;
	int nHappyNode = 0;
	
	// Statistics
	CString str;
	POSITION posNode = m_nodeList.GetHeadPosition();
	while (posNode != NULL)
	{
		CNode* pNode = (CNode*)m_nodeList.GetAt(posNode);
		if (pNode->strType == "Sink")
		{
			str.Format("Rate of Sink %d is %d.\r\n", pNode->nNodeID, pNode->nMaxflow);
			m_strOutput += str;
			nTotalRate += pNode->nMaxflow;
			if (pNode->nMaxflow == pNode->nOriginalMaxflow)
			{
				nHappyNode++;
			}
			
		}
		m_nodeList.GetNext(posNode);
	}
	
	str.Format("Total rate is %d.\r\n", nTotalRate);
	m_strOutput += str;
	str.Format("The number of HappyNode is %d.\r\n", nHappyNode);
	m_strOutput += str;
	
	
	int nTotalLinkNum = 0;
	int nUsedLinkNum = 0;
	POSITION posLink = m_linkList.GetHeadPosition();
	while (posLink != NULL)
	{
		CLink* pLink = (CLink*)m_linkList.GetAt(posLink);
		nTotalLinkNum++;
		if (pLink->bInSubGraph == TRUE)
		{
			nUsedLinkNum++;
		}
		m_linkList.GetNext(posLink);
	}
	
	
	str.Format("Link Usage Rate: %d/%d.", nUsedLinkNum, nTotalLinkNum);
	m_strOutput += str;
	
	
	UpdateData(false);
	InvalidateRect(false);
}

void CSRNC_ConstructorDlg::UsingDeterministicAlgorithm()
{
	// Using deterministic network coding
	// Determine the required field size.
	int nSinkCnt = 0;
	int N = m_nMulticastCapacity;
	POSITION pos = m_nodeList.GetHeadPosition();
	while (pos != NULL)
	{
		CNode* pNode = (CNode*)m_nodeList.GetAt(pos);
		if (pNode->strType == "Sink")
		{
			// Allocate memory for these sink nodes.
			UINT **RM = new UINT*[N];		
			for(int i=0; i < N; i++)
				RM[i] = new UINT[N];
			// Initialize the RM with identity vectors.
			for (i=0; i<N; i++)
			{
				for (int j=0; j<N; j++)
				{
					if (i == j)
					{
						RM[i][j] = 1;
					}
					else
					{
						RM[i][j] = 0;
					}
				}
			}
			pNode->nRM = RM;
			
			nSinkCnt++;
		}
		m_nodeList.GetNext(pos);
	}
	
	// Trace for test.
	/*	pos = m_nodeList.GetHeadPosition();
	while (pos != NULL)
	{
	CNode* pNode = (CNode*)m_nodeList.GetAt(pos);
	if (pNode->strType == "Sink")
	{
	for (int i=0; i<N; i++)
	{
				for (int j=0; j<N; j++)
				{
				TRACE("%d ", pNode->nRM[i][j]);
				}
				TRACE("\n");
				}
				TRACE("&&&%d\n", pNode->nNodeID);
				
				  }
				  m_nodeList.GetNext(pos);
				  
					}
	*/
	
	//		nSinkCnt = 9;			// for test.
	int m = 1;  // GF(2^m), start from m = 1;
	while (1)
	{
		if ((1<<m) > nSinkCnt)
		{
			int nOrder = m;
			m_nOrder = nOrder;
			gf_init(nOrder, prim_poly[nOrder]);
			break;
		}
		m++;
	}
	
	// So far, field size has been defined.
	
	/************************************************************************/
	/* Start to assign network codes in the topological order.              */
	/************************************************************************/
	// First, set the input links of the outgoing links of the source node.
	// Since there is a virtual node, so all the outgoing links has N input links. 
	// Actually, these nodes don't have any input link. So, we need to first assign network codes for them.
	pos = m_linkList.GetHeadPosition();
	
	while (pos != NULL)
	{
		CLink* pLink = (CLink*)m_linkList.GetAt(pos);
		if (pLink->nStartAt == m_nSrcID)
		{
			// To know how many sink node occupying this link.
			int nSharedBy = 0;				// The number of sink node using this link.
			POSITION posNode = m_nodeList.GetHeadPosition();
			while (posNode != NULL)
			{
				CNode* pNode = (CNode*)m_nodeList.GetAt(posNode);
				if (pNode->strType == "Sink")
				{
					
					bool bFind = false;
					for (int i=0; i<N; i++)
					{
						for (int j=0; j<20; j++)
						{
							if (pNode->nRoutes[i][j] == pLink->nLinkNum)
							{
								nSharedBy++;
								bFind = true;
								break;
							}
						}
						if (bFind == TRUE)
						{
							break;
						}
						
					}
				}
				m_nodeList.GetNext(posNode);
				
			}
			// Now, we got the number of nSharedBy;
			
			// Then we need to new two matrices, one is used to store U, and the other is used to store V.
			// U is the vectors will be replaced, and V is the orthocomplement vector after removing U.
			// The dimension of the two matrices must be "nSharedBy".
			UINT **USet = new UINT*[nSharedBy];			// RemainM is the matrix after removing a vector.
			for(int j=0; j<nSharedBy; j++)
			{
				USet[j] = new UINT[N];
			}
			UINT **VSet = new UINT*[nSharedBy];			// RemainM is the matrix after removing a vector.
			for( j=0; j<nSharedBy; j++)
			{
				VSet[j] = new UINT[N];
			}
			int nCnt = 0;								// Used when insert U and V to USet and VSet.
			
			//  Calculate the vectors for U and V.
			posNode = m_nodeList.GetHeadPosition();
			while (posNode != NULL)
			{
				CNode* pNode = (CNode*)m_nodeList.GetAt(posNode);
				if (pNode->strType == "Sink")
				{
					// Used to indicate which GCV will be removed. At initial stage, route i conresonds to ei.
					int nI = -1;
					// Check whether this link is in the routes.
					bool bFind = FALSE;
					for (int i=0; i<N; i++)
					{
						for (int j=0; j<20; j++)
						{
							if (pNode->nRoutes[i][j] == pLink->nLinkNum)
							{
								nI = i;
								pNode->nI = i;				// for updating the RM matrix.
								// Copy the conresponding vector in nRM to U.
								bFind = TRUE;
								break;
							}
						}
						if (bFind == TRUE)
						{
							break;
						}
						
					}
					if (bFind == TRUE)
					{
						
						// Calculate orthocomplement vector (namely V). New a (N-1)-by-N matrix, and new a N-dimensional vector.
						
						UINT *OCV = new UINT[N];					// OCM is used to store the orthocomplement vector.
						for (int z=0; z<N; z++)
						{
							OCV[z] = 0;
						}
						
						GetOCV(pNode->nRM, OCV, nI);
						for (i=0; i<N; i++)
						{
							TRACE("%d ", OCV[i]);
						}
						TRACE("\n");
						
						
						for (z=0; z<N; z++)
						{
							USet[nCnt][z] = pNode->nRM[nI][z];
						}
						
						for (i=0; i<N; i++)
						{
							VSet[nCnt][i] = OCV[i];
						}
						nCnt++;
						
						
						delete[] OCV;
						
						
					}
					
					
				}
				
				m_nodeList.GetNext(posNode);
			}
			
			// Trace the vectors in U and V;
			// 			TRACE("@@@@@@@@@\n");
			// 			for (int k=0; k<nSharedBy; k++)
			// 			{
			// 				for (int j=0; j<N; j++)
			// 				{
			// 					TRACE("%d ", USet[k][j]);
			// 				}
			// 				TRACE("\n");
			// 			}
			// 			TRACE("U####\n");
			// 			for (k=0; k<nSharedBy; k++)
			// 			{
			// 				for (int j=0; j<N; j++)
			// 				{
			// 					TRACE("%d ", VSet[k][j]);
			// 				}
			// 				TRACE("\n");
			// 			}
			// 			TRACE("V####\n");
			
			// 后面所有要做的就是根据这两个集合来求一个共同的线性组合。满足原文中的定理，难道要用数学归纳法？
			
			// Define a vector r which is a linear combination of vectors in USet.
			
			UINT *r = new UINT[N];
			for (int i=0; i<N; i++)
			{
				r[i] = 0;
			}
			// COEFF
			// 			UINT *Lambda  = new UINT[N];
			// 			for (int i=0; i<N; i++)
			// 			{
			// 				Lambda[i] = 0;
			// 			}
			
			for (i=1; i<=nSharedBy; i++)			// nSharedby is the n in S Jaggi's paper.
			{
				if (i==1)
				{
					// r = u1
					for (int j=0; j<N; j++)
					{
						r[j] = USet[0][j];
					}
					//					Lambda[0] = 1;
				}
				else if (i > 1)
				{
					int temp = 0;
					for (int j=0; j<N; j++)
					{
						temp = gf_add(temp, gf_mul(r[j], VSet[i-1][j]));
					}
					if (temp == 0)
					{
						// Define an array to indicate whether the elements is in λ
						int nSize = 1<<m_nOrder;
						bool *Elem = new bool[nSize];
						for (int z=0; z<nSize; z++)
						{
							Elem[z] = FALSE;
						}
						
						
						// 进一步修改R
						for (int j=0; j<i-1; j++)
						{
							int nRes1 = 0;
							for (int z=0; z<N; z++)
							{
								nRes1 = gf_add(nRes1, gf_mul(USet[i-1][z], VSet[j][z]));
							}
							
							int nRes2 = 0;
							for (z=0; z<N; z++)
							{
								nRes2 = gf_add(nRes2, gf_mul(r[z], VSet[j][z]));
							}
							
							int nRes = gf_div(nRes1, nRes2);
							
							Elem[nRes] = TRUE;
							
						}
						// Select the element which is false to be the Coefficient λ
						int nCoeff = 0;
						for (int x=nSize-1; x>=0; x--)
						{
							if (Elem[x] == FALSE)
							{
								nCoeff = x;
								break;
							}
						}
						// Obtain r(k+1) = λr(k) + u(k+1);
						for (x=0; x<N; x++)
						{
							r[x] = gf_add(gf_mul(nCoeff, r[x]), USet[i-1][x]);
						}
						
						delete[] Elem;
					}			
					
				}
				
			}
			
			for (j=0; j<N; j++)
			{
				pLink->GCV[j] = r[j];
				
			}
			// Update pNode->nRM matrix.
			posNode = m_nodeList.GetHeadPosition();
			while (posNode != NULL)
			{
				CNode* pNode = (CNode*)m_nodeList.GetAt(posNode);
				if (pNode->strType == "Sink")
				{
					
					// Check whether this link is in the routes.
					bool bFind = FALSE;
					for (int i=0; i<N; i++)
					{
						for (int j=0; j<20; j++)
						{
							if (pNode->nRoutes[i][j] == pLink->nLinkNum)
							{
								bFind = TRUE;
								break;
							}
						}
						if (bFind == TRUE)
						{
							break;
						}
						
					}
					if (bFind == TRUE)
					{
						for (int x=0; x<N; x++)
						{
							int nCur = pNode->nI;
							pNode->nRM[nCur][x] = r[x];
							
						}
					}
				}
				m_nodeList.GetNext(posNode);
				
			}
			pLink->bAssigned = TRUE;
			// Release matrix USet and VSet.
			for( i = 0; i < nSharedBy; i++) 
			{
				delete []USet[i];
			}
			delete []USet; 
			for( i = 0; i < nSharedBy; i++) 
			{
				delete []VSet[i];
			}
			delete []VSet; 
			
			delete []r;
			
		}
		m_linkList.GetNext(pos);
	}
	
	while (1)
	{
		bool bAllLinkAssigned = TRUE;
		pos = m_linkList.GetHeadPosition();
		// Endless loop till all the links are assigned GEVs.
		while (pos != NULL)
		{
			CLink* pLink = (CLink*)m_linkList.GetAt(pos);
			if (pLink->nStartAt !=  m_nSrcID && pLink->bAssigned == false)
			{
				// Check whether all the input links of this link have been assigned.
				if (pLink->nInputLink == 1)
				{
					// if its previous link is assigned, copy the GCV.
					if (PreLinkAssigned(pLink->nPreLink[0]) == TRUE)
					{
						// copy the GCV
						for (int z=0; z<m_nMulticastCapacity; z++)
						{
							pLink->GCV[z] = m_pPreLink->GCV[z];
							
						}
						pLink->LCV[0] = 1;
						pLink->bAssigned = TRUE;
					}
					else
					{
						bAllLinkAssigned = FALSE;
					}
				}
				else
				{
					int nPre = pLink->nInputLink;
					bool bAllPreAssigned = TRUE;
					for (int j=0; j<nPre; j++)
					{
						if (PreLinkAssigned(pLink->nPreLink[j]) == FALSE)
						{
							bAllPreAssigned = FALSE;
						}
					}
					if (bAllPreAssigned == TRUE)
					{
						// All input links are assigned GEV, this link can be assigned now.
						// To know how many sink node occupying this link.
						int nSharedBy = 0;				// The number of sink node using this link.
						POSITION posNode = m_nodeList.GetHeadPosition();
						while (posNode != NULL)
						{
							CNode* pNode = (CNode*)m_nodeList.GetAt(posNode);
							if (pNode->strType == "Sink")
							{
								
								bool bFind = false;
								for (int i=0; i<N; i++)
								{
									for (int j=0; j<20; j++)
									{
										if (pNode->nRoutes[i][j] == pLink->nLinkNum)
										{
											nSharedBy++;
											bFind = true;
											break;
										}
									}
									if (bFind == TRUE)
									{
										break;
									}
									
								}
							}
							m_nodeList.GetNext(posNode);
							
						}
						UINT **USet = new UINT*[nSharedBy];			// RemainM is the matrix after removing a vector.
						for(int j=0; j<nSharedBy; j++)
						{
							USet[j] = new UINT[N];
						}
						UINT **VSet = new UINT*[nSharedBy];			// RemainM is the matrix after removing a vector.
						for( j=0; j<nSharedBy; j++)
						{
							VSet[j] = new UINT[N];
						}
						int nCnt = 0;								// Used when insert U and V to USet and VSet.
						
						//  Calculate the vectors for U and V.
						posNode = m_nodeList.GetHeadPosition();
						while (posNode != NULL)
						{
							CNode* pNode = (CNode*)m_nodeList.GetAt(posNode);
							if (pNode->strType == "Sink")
							{
								// Used to indicate which GCV will be removed. At initial stage, route i conresonds to ei.
								int nI = -1;
								// Check whether this link is in the routes.
								bool bFind = FALSE;
								for (int i=0; i<N; i++)
								{
									for (int j=0; j<20; j++)
									{
										if (pNode->nRoutes[i][j] == pLink->nLinkNum)
										{
											nI = i;
											pNode->nI = i;				// for updating the RM matrix.
											// Copy the conresponding vector in nRM to U.
											bFind = TRUE;
											break;
										}
									}
									if (bFind == TRUE)
									{
										break;
									}
									
								}
								if (bFind == TRUE)
								{
									
									// Calculate orthocomplement vector (namely V). New a (N-1)-by-N matrix, and new a N-dimensional vector.
									
									UINT *OCV = new UINT[N];					// OCM is used to store the orthocomplement vector.
									for (int z=0; z<N; z++)
									{
										OCV[z] = 0;
									}
									
									GetOCV(pNode->nRM, OCV, nI);
									for (i=0; i<N; i++)
									{
										TRACE("%d ", OCV[i]);
									}
									TRACE("\n");
									
									
									for (z=0; z<N; z++)
									{
										USet[nCnt][z] = pNode->nRM[nI][z];
									}
									
									for (i=0; i<N; i++)
									{
										VSet[nCnt][i] = OCV[i];
									}
									nCnt++;
									
									
									delete[] OCV;
									
									
								}
								
								
							}
							
							m_nodeList.GetNext(posNode);
						}
						//
						// Define a vector r which is a linear combination of vectors in USet.
						
						UINT *r = new UINT[N];
						for (int i=0; i<N; i++)
						{
							r[i] = 0;
						}
						
						for (i=1; i<=nSharedBy; i++)			// nSharedby is the n in S Jaggi's paper.
						{
							if (i==1)
							{
								// r = u1
								for (int j=0; j<N; j++)
								{
									r[j] = USet[0][j];
								}
							}
							else if (i > 1)
							{
								int temp = 0;
								for (int j=0; j<N; j++)
								{
									temp = gf_add(temp, gf_mul(r[j], VSet[i-1][j]));
								}
								if (temp == 0)
								{
									// Define an array to indicate whether the elements is in λ
									int nSize = 1<<m_nOrder;
									bool *Elem = new bool[nSize];
									for (int z=0; z<nSize; z++)
									{
										Elem[z] = FALSE;
									}
									
									
									// Further change R
									for (int j=0; j<i-1; j++)
									{
										int nRes1 = 0;
										for (int z=0; z<N; z++)
										{
											nRes1 = gf_add(nRes1, gf_mul(USet[i-1][z], VSet[j][z]));
										}
										
										int nRes2 = 0;
										for (z=0; z<N; z++)
										{
											nRes2 = gf_add(nRes2, gf_mul(r[z], VSet[j][z]));
										}
										
										int nRes = gf_div(nRes1, nRes2);
										
										Elem[nRes] = TRUE;
										
									}
									// 选取第一个不为true的Elem来作为系数λ(nCoeff)
									int nCoeff = 0;
									for (int x=nSize-1; x>=0; x--)
									{
										if (Elem[x] == FALSE)
										{
											nCoeff = x;
											break;
										}
									}
									// Obtain r(k+1) = λr(k) + u(k+1);
									for (x=0; x<N; x++)
									{
										r[x] = gf_add(gf_mul(nCoeff, r[x]), USet[i-1][x]);
									}
									
									delete[] Elem;
								}			
								
							}
							
						}
						
						for (j=0; j<N; j++)
						{
							pLink->GCV[j] = r[j];
							
						}
						// updata pNode->nRM matrix.
						posNode = m_nodeList.GetHeadPosition();
						while (posNode != NULL)
						{
							CNode* pNode = (CNode*)m_nodeList.GetAt(posNode);
							if (pNode->strType == "Sink")
							{
								
								// Check whether this link is in the routes.
								bool bFind = FALSE;
								for (int i=0; i<N; i++)
								{
									for (int j=0; j<20; j++)
									{
										if (pNode->nRoutes[i][j] == pLink->nLinkNum)
										{
											bFind = TRUE;
											break;
										}
									}
									if (bFind == TRUE)
									{
										break;
									}
									
								}
								if (bFind == TRUE)
								{
									for (int x=0; x<N; x++)
									{
										int nCur = pNode->nI;
										pNode->nRM[nCur][x] = r[x];
										
									}
								}
							}
							m_nodeList.GetNext(posNode);
							
						}
						pLink->bAssigned = TRUE;
						// Release matrix USet and VSet.
						for( i = 0; i < nSharedBy; i++) 
						{
							delete []USet[i];
						}
						delete []USet; 
						for( i = 0; i < nSharedBy; i++) 
						{
							delete []VSet[i];
						}
						delete []VSet; 
						
						delete []r;
						
						
					}
					else
					{
						bAllLinkAssigned = FALSE;
					}
					
				}
			}
			m_linkList.GetNext(pos);
			
		}
		if (bAllLinkAssigned == TRUE)
		{
			break;
		}
		
	}
	
	
	
	
	// Release memory
	pos = m_nodeList.GetHeadPosition();
	while (pos != NULL)
	{
		CNode* pNode = (CNode*)m_nodeList.GetAt(pos);
		if (pNode->strType == "Sink")
		{
			for( int i = 0; i < N; i++) 
			{
				delete [](pNode->nRM)[i];
			}
			delete []pNode->nRM; 
		}
		m_nodeList.GetNext(pos);
	}
	
	gf_uninit();
}


unsigned int Rank(GFType **G, GFType nRow, GFType nCol)
{ 
	int **M = new int*[nRow];
	for(int j=0; j<nRow; j++)
	{
		M[j] = new int[nCol];
	}		
	
	
	for (int i=0; i<nRow; i++)
	{
		for (int j=0; j<nCol; j++)
		{
			//printf("%d\t", *((GFType*)G + nCol*i + j));
			// M[i][j] = *((GFType*)G + nCol*i + j);
			M[i][j] = *(*(G + i) + j);
		}
		// printf("\n");
	}
	// printf("\n");
	
	for (i=0; i<nRow; i++)
	{
		for (int j=0; j<nCol; j++)
		{
			TRACE("%d\t", M[i][j]);
		}
		TRACE("\n");
	}
	TRACE("\n");
	
	// Define a variable to record the position of the main element.
	int yPos = 0;
	
	for (i=0; i<nRow; i++)
	{
		// Find the main element which must be non-zero.
		
		bool bFind = false;
		
		for (int x=yPos; x<nCol; x++)
		{
			for (int k=i; k<nRow; k++)
			{
				if (M[k][x] != 0)
				{
					// Exchange the two vectors.
					for (int x=0; x<nCol; x++)
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
		
		
		
		for (int j=i+1; j<nRow; j++)
		{
			// Now, the main element must be nonsingular.
			GFType temp = gf_div(M[j][yPos], M[i][yPos]);
			for (int z=0; z<nCol; z++)
			{
				M[j][z] = gf_add(M[j][z], gf_mul(temp, M[i][z]));
			}
		}
		// 
		yPos++;
		
	}
	
	// The matrix becomes a scalar matrix. we need to make more elements become 0 with elementary transformations.
	yPos = 0;
	for (i=1;i<nRow;i++)
	{
		for (int j=0;j<nCol;j++)
		{
			if (M[i][j] != 0)
			{
				// the main element is found.
				yPos = j;
				break;
			}
		}
		for (int k=0; k<i;k++)
		{
			GFType temp = gf_div(M[k][yPos], M[i][yPos]);
			for (int z=0; z<nCol; z++)
			{
				M[k][z] = gf_add(M[k][z], gf_mul(temp, M[i][z]));
			}
		}
	}
	
	int nRank = 0;
	// Get the rank.
	for (i=0; i<nRow; i++)
	{
		int nNonzero = 0;				
		for (j=0; j<nCol; j++)
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
	
	
	
	for (i=0; i<nRow; i++) 
	{
		delete []  M[i]; 
	}
	delete[] M;
	
	return nRank;
}

void CSRNC_ConstructorDlg::GetOCV(UINT **G, UINT *OCV, int nI)
{
	// This function is used to obtain the orthocomplement vector.
	// The dimensional of vectors in RemainM and OCV is m_nMulticastCapacity.
	
	int nRow = m_nMulticastCapacity;
	int nCol = nRow;
	
	/************************************************************************/
	/* Note: the N here is a matrix, and the N above is the multicast       */
    /* capacity. Sorry for this inconvenience.                              */
	/************************************************************************/
	int **N = new int*[nCol];
	for(int j=0; j<nCol; j++)
	{
		N[j] = new int[2*nCol];
	}
	
	for (int i=0; i<nCol; i++)
	{
		for (int j=0; j<nCol; j++)
		{
			N[i][j] = *(*(G + i) + j);;
			TRACE("%d\t", N[i][j]);
		}
		for (j=nCol; j<2*nCol; j++)
		{
			if (i == j-nCol)
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
	
	for (i=0; i<nCol; i++)
	{
		// There must exist a non-zero mainelement.
		TRACE("*********\n");
		if (N[i][i] == 0)
		{
			// Record this line.
			int temp[200] = {0};
			for (int k=0; k<2*nCol; k++)
			{
				temp[k] = N[i][k];
			}
			// Exchange
			int nRow = nCol;					// They are the same in essensial.
			for (int z=i+1; z<nRow; z++)
			{
				if (N[z][i]!=0)
				{
					for (int x=0; x<2*nCol; x++)
					{
						N[i][x] = N[z][x];
						N[z][x] = temp[x];
					}
					break;
				}
			}
			
		}
		
		
		for (int j=i+1; j<nCol; j++)
		{
			// Now, the main element must be nonsingular.
			GFType temp = gf_div(N[j][i], N[i][i]);
			for (int z=0; z<2*nCol; z++)
			{
				N[j][z] = gf_add(N[j][z], gf_mul(temp, N[i][z]));
			}
		}
	}
	/************************************************************************/
	/* Step 2. Only the elements on the diagonal are non-zero.              */
	/************************************************************************/
	for (i=1;i<nCol;i++)
	{
		for (int k=0; k<i;k++)
		{
			GFType temp = gf_div(N[k][i], N[i][i]);
			for (int z=0; z<2*nCol; z++)
			{
				N[k][z] = gf_add(N[k][z], gf_mul(temp, N[i][z]));
			}
		}
	}
	/************************************************************************/
	/* Step 3. The elements on the diagonal are 1.                          */
	/************************************************************************/
	for (i=0; i<nCol; i++)
	{
		if (N[i][i]!=1)
		{
			GFType temp = N[i][i];
			for (int z=0; z<2*nCol; z++)
			{
				N[i][z] = gf_div(N[i][z], temp);
			}
		}
	}
	// Copy the orthocomplement vector to OCV;
	for (i=0; i<nRow; i++)			// nRow = nCol
	{
		OCV[i] = N[i][nRow+nI];
	}
	
	// Release
	for (i=0; i<nCol; i++)
	{
		delete []  N[i]; 	
	}
	delete N;
	
	
}

void CSRNC_ConstructorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	POSITION posLinkDel = m_linkList.GetHeadPosition();
	while (posLinkDel != NULL)
	{
		CLink* pLink = (CLink*)m_linkList.GetAt(posLinkDel);
		delete pLink;
		
		m_linkList.GetNext(posLinkDel);
	}
	POSITION posNodeDel = m_nodeList.GetHeadPosition();
	while (posNodeDel != NULL)
	{
		CNode* pLink = (CNode*)m_nodeList.GetAt(posNodeDel);
		delete pLink;
		
		m_nodeList.GetNext(posNodeDel);
	}
	
	m_nodeList.RemoveAll();
	m_linkList.RemoveAll();
}

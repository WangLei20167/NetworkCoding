// Network_Topology_GeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Network_Topology_Generator.h"
#include "Network_Topology_GeneratorDlg.h"
#include "Node.h"
#include "Link.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CNetwork_Topology_GeneratorDlg dialog

CNetwork_Topology_GeneratorDlg::CNetwork_Topology_GeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetwork_Topology_GeneratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetwork_Topology_GeneratorDlg)
	m_nRadio = -1;
	m_strOut = _T("");
	m_nNodeNum = 0;
	m_nSinkNumber = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bAllowAddNode = FALSE;
	m_bAllowAddLink = false;
	m_bAllowDeleteLink = false;
	m_bAllowDeleteNode = FALSE;
	m_bMoveNode = FALSE;
	m_bAllowMoveNode = FALSE;
}

void CNetwork_Topology_GeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetwork_Topology_GeneratorDlg)
	DDX_Radio(pDX, IDC_RADIO_Source, m_nRadio);
	DDX_Text(pDX, IDC_EDIT1, m_strOut);
	DDX_Text(pDX, IDC_EDIT_NodeNum, m_nNodeNum);
	DDX_Text(pDX, IDC_EDIT_SinkNumber, m_nSinkNumber);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetwork_Topology_GeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CNetwork_Topology_GeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Import, OnBUTTONImport)
	ON_BN_CLICKED(IDC_BUTTON_PlaceNode, OnBUTTONPlaceNode)
	ON_BN_CLICKED(IDC_BUTTON_DeleteNode, OnBUTTONDeleteNode)
	ON_BN_CLICKED(IDC_BUTTON_PlaceLink, OnBUTTONPlaceLink)
	ON_BN_CLICKED(IDC_BUTTON_DeleteLink, OnBUTTONDeleteLink)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_MoveNode, OnBUTTONMoveNode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetwork_Topology_GeneratorDlg message handlers

BOOL CNetwork_Topology_GeneratorDlg::OnInitDialog()
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
	m_nRadio = 0;

	m_nNodeNum = 10;
	m_nSinkNumber = 3;
	GetCurrentDirectory(MAX_PATH, m_szPath);

//	m_nUpBound = 5;
//	m_nLowBound = 3;
	

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetwork_Topology_GeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetwork_Topology_GeneratorDlg::OnPaint() 
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

	DrawLinkAndNode();
	

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetwork_Topology_GeneratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNetwork_Topology_GeneratorDlg::OnBUTTONImport() 
{
	// TODO: Add your control notification handler code here
	m_nodeList.RemoveAll();
	m_linkList.RemoveAll();
	
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
	
	Invalidate(false);
}
void CNetwork_Topology_GeneratorDlg::DrawArrow(CPoint p1, CPoint p2, double theta, int length)
{
	theta=3.1415926*theta/180;//转换为弧度
	double Px,Py,P1x,P1y,P2x,P2y;
	//以P2为原点得到向量P2P1（P）
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	//向量P旋转theta角得到向量P1
	P1x=Px*cos(theta)-Py*sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//伸缩向量至制定长度
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;
	//平移变量到直线的末端
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	CClientDC dc(this);//获取客户窗口DC
	// 	CPen pen,pen1,*oldpen;
	// 	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	// 	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	// 	oldpen=dc.SelectObject(&pen);
//	dc.MoveTo(p1.x,p1.y);
//	dc.LineTo(p2.x,p2.y);
	// 	dc.SelectObject(&pen1);
	dc.MoveTo(p2.x,p2.y);
	dc.LineTo(P1x,P1y);
	dc.MoveTo(p2.x,p2.y);
	dc.LineTo(P2x,P2y);
	
	// 	dc.SelectObject(oldpen);
}

void CNetwork_Topology_GeneratorDlg::OnBUTTONPlaceNode() 
{
	// TODO: Add your control notification handler code here
	m_bAllowAddNode = TRUE;
	m_bAllowDeleteNode = FALSE;
	m_bAllowAddLink = FALSE;
	m_bAllowDeleteLink = FALSE;
	m_bAllowMoveNode = FALSE;
}

void CNetwork_Topology_GeneratorDlg::OnBUTTONDeleteNode() 
{
	// TODO: Add your control notification handler code here
	m_bAllowDeleteNode = TRUE;
	m_bAllowAddNode = FALSE;
	m_bAllowAddLink = FALSE;
	m_bAllowDeleteLink = FALSE;
	m_bAllowMoveNode = FALSE;
}

void CNetwork_Topology_GeneratorDlg::OnBUTTONPlaceLink() 
{
	// TODO: Add your control notification handler code here
	m_bAllowAddNode = FALSE;
	m_bAllowDeleteNode = FALSE;
	m_bAllowAddLink = TRUE;
	m_bAllowDeleteLink = FALSE;
	m_bAllowMoveNode = FALSE;
}

void CNetwork_Topology_GeneratorDlg::OnBUTTONDeleteLink() 
{
	// TODO: Add your control notification handler code here
	m_bAllowDeleteLink = TRUE;
	m_bAllowAddLink = FALSE;
	m_bAllowAddNode = FALSE;
	m_bAllowDeleteNode = FALSE;
	m_bAllowMoveNode = FALSE;
}

void CNetwork_Topology_GeneratorDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	m_nodeList.RemoveAll();
	m_linkList.RemoveAll();
	
	InvalidateRect(FALSE);
}

void CNetwork_Topology_GeneratorDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	FILE *pFile = NULL;
	CString strfilename;
	CTime curTime = CTime::GetCurrentTime();
	

	SetCurrentDirectory(m_szPath);
	CString strPath;
	strPath.Format("%s%s", m_szPath, "/topology");
	bool bRet = DirectoryExist(strPath);
	if (bRet == FALSE)
	{
		CreateDirectory(strPath, NULL);
	}
	
	strfilename.Format("topology/Topology_%d_%d_%d_%d_%d_%d.topo",curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
	
	pFile = fopen(LPCTSTR(strfilename),"a");
	
	int nodeNumber = m_nodeList.GetCount();
	int linkNumber = m_linkList.GetCount();
	fprintf(pFile,"%d %d\n", nodeNumber, linkNumber);
	
	fprintf(pFile,"NodeList\n");
	
	// Traverse the node list.
	POSITION pos;	
	pos = m_nodeList.GetHeadPosition();
	CNode *myNode;
	
	while (pos != NULL)
	{
		myNode = (CNode *)m_nodeList.GetAt(pos);
		fprintf(pFile, "%s %d %d\n", myNode->strType, myNode->nXPos, myNode->nYPos);
		m_nodeList.GetNext(pos);
	}
	fprintf(pFile,"\n");
	
	fprintf(pFile,"LinkList\n");
	
	// Traverse the link list.
	POSITION posLink;	
	posLink = m_linkList.GetHeadPosition();
	CLink *pLink;
	while (posLink != NULL)
	{
		pLink = (CLink *)m_linkList.GetAt(posLink);
		
		fprintf(pFile, "%s %d %d %d %d\n", "S", pLink->posStartPos.x, pLink->posStartPos.y, pLink->posEndPos.x, pLink->posEndPos.y);
		m_linkList.GetNext(posLink);
	}
	
	
	fclose(pFile);
	CString msg("Ok. The file name is\n");
	msg = msg+strfilename;
	
	MessageBox(msg);
}

void CNetwork_Topology_GeneratorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bAllowAddLink == TRUE || m_bAllowMoveNode == TRUE)
	{
		m_LatestPos = point;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CNetwork_Topology_GeneratorDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bAllowAddLink == TRUE)
	{
		CPoint curPos;
		curPos = point;
		
		CPoint posLinkStart, posLinkEnd;
		bool bFindA = FALSE;
		bool bFindB = FALSE;
		
		// Start to find the corresponding node.
		POSITION pos;	
		pos = m_nodeList.GetHeadPosition();
		CNode *myNode;
		while (pos != NULL)
		{
			myNode = (CNode *)m_nodeList.GetAt(pos);
			
			if (abs(myNode->nXPos-m_LatestPos.x)<5 && abs(myNode->nYPos-m_LatestPos.y)<5)
			{
				posLinkStart.x = myNode->nXPos;
				posLinkStart.y = myNode->nYPos;
				bFindA = TRUE;
			}
			if (abs(myNode->nXPos-curPos.x)<5 && abs(myNode->nYPos-curPos.y)<5)
			{
				posLinkEnd.x = myNode->nXPos;
				posLinkEnd.y = myNode->nYPos;
				bFindB = TRUE;
			}
			
			m_nodeList.GetNext(pos);
		}
		
		// Insert a link into the LinkList.
		if ((posLinkStart != posLinkEnd) && bFindA && bFindB)
		{
			CLink* pLink = new CLink;
			pLink->posStartPos = posLinkStart;
			pLink->posEndPos = posLinkEnd;
			m_linkList.AddTail((CObject *)pLink);
			
		}
		
	}
	else if (m_bAllowMoveNode == TRUE)
	{
		CPoint curPos;
		curPos = point;
		
		// Start to find the corresponding node.
		POSITION pos;	
		pos = m_nodeList.GetHeadPosition();
		CNode *myNode;
		while (pos != NULL)
		{
			myNode = (CNode *)m_nodeList.GetAt(pos);
			
			if (abs(myNode->nXPos-m_LatestPos.x)<5 && abs(myNode->nYPos-m_LatestPos.y)<5)
			{
				// 修正m_LatestPos
				m_LatestPos.x = myNode->nXPos;
				m_LatestPos.y = myNode->nYPos;
				
				myNode->nXPos = curPos.x;
				myNode->nYPos = curPos.y;

				// Update all the link in the list.
				POSITION linkPos;
				linkPos = m_linkList.GetHeadPosition();
				CLink *pLink;
				while (linkPos != NULL)
				{
					pLink = (CLink *)m_linkList.GetAt(linkPos);
					if (pLink->posStartPos == m_LatestPos)
					{
						pLink->posStartPos = curPos;
					}
					else if (pLink->posEndPos == m_LatestPos)
					{
						pLink->posEndPos = curPos;
					}
					m_linkList.GetNext(linkPos);
					
				}

				break;
			}

			m_nodeList.GetNext(pos);
		}

		
	}
	
	
	InvalidateRect(FALSE);	
	CDialog::OnLButtonUp(nFlags, point);
}

void CNetwork_Topology_GeneratorDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	if (m_bAllowAddNode == TRUE)
	{
		
		CNode* pNode = new CNode;
		// Initialize
		pNode->nXPos = point.x;
		pNode->nYPos = point.y;
		
		if (m_nRadio == 0)
		{
			pNode->strType = "Source";
		}
		else if (m_nRadio == 1)
		{
			pNode->strType = "Relay";
		}
		else if (m_nRadio == 2)
		{
			pNode->strType = "Sink";
		}
		
		m_nodeList.AddTail((CObject *)pNode);
		
	}
	if (m_bAllowDeleteNode == TRUE)
	{
		// Start to delete.
		POSITION pos, posCopy;	
		pos = m_nodeList.GetHeadPosition();
		CNode *myNode;
		bool bFind = FALSE;
		while (pos != NULL)
		{
			myNode = (CNode *)m_nodeList.GetAt(pos);
			if (abs(myNode->nXPos-point.x)<=5 && abs(myNode->nYPos-point.y)<=5)
			{
				posCopy = pos;
				bFind = TRUE;
				break;
			}
			
			m_nodeList.GetNext(pos);
		}
		if (bFind == TRUE)
		{
			// Delete all the accociated links before deleting the node.
			POSITION posLink;	
			posLink = m_linkList.GetHeadPosition();
			CLink *pLink;
			while (posLink != NULL)
			{
				pLink = (CLink *)m_linkList.GetAt(posLink);
				
				if (((pLink->posStartPos.x == myNode->nXPos) && (pLink->posStartPos.y == myNode->nYPos)) || ((pLink->posEndPos.x == myNode->nXPos) && (pLink->posEndPos.y == myNode->nYPos)))
				{
					POSITION posTemp = posLink;
					m_linkList.GetNext(posLink);
					m_linkList.RemoveAt(posTemp);				
				}
				else
				{
					m_linkList.GetNext(posLink);
				}
						
			}
			
			m_nodeList.RemoveAt(posCopy);
		}
		
	}
	
	if (m_bAllowDeleteLink == TRUE)
	{
		int x1 = point.x;
		int y1 = point.y;
		
		POSITION posLink;	
		posLink = m_linkList.GetHeadPosition();
		CLink *pLink;
		while (posLink != NULL)
		{
			pLink = (CLink *)m_linkList.GetAt(posLink);
			
			double a = pLink->posEndPos.y - pLink->posStartPos.y;
			double b = pLink->posStartPos.x - pLink->posEndPos.x;
			double c = (pLink->posEndPos.x * pLink->posStartPos.y) - (pLink->posStartPos.x * pLink->posEndPos.y);
 			double h = abs(a*x1 + b* y1 + c)/sqrt(a*a + b*b);
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
			
			
			if ((x1>nXSmall&&x1<nXBig || y1<nYBig&&y1>nYSmall) && h<=5)
			{
				m_linkList.RemoveAt(posLink);
				break;

			}
			else
			{
				m_linkList.GetNext(posLink);
			}
			
		}
		
	}
	
	InvalidateRect(FALSE);
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CNetwork_Topology_GeneratorDlg::DrawLinkAndNode()
{
	CClientDC dc(this);
	POSITION posLink;	
	posLink = m_linkList.GetHeadPosition();
	CLink *pLink;
	while (posLink != NULL)
	{
		pLink = (CLink *)m_linkList.GetAt(posLink);
		
		dc.MoveTo(pLink->posStartPos);
		dc.LineTo(pLink->posEndPos);
		// Add a small arrow
		DrawArrow(pLink->posStartPos, pLink->posEndPos, 10, 12);
		
		m_linkList.GetNext(posLink);
	}
	
	POSITION pos;	
	pos = m_nodeList.GetHeadPosition();
	CNode *myNode;
	while (pos != NULL)
	{
		myNode = (CNode *)m_nodeList.GetAt(pos);
		CBrush *pBrush;
		if (myNode->strType == "Source")
		{
			pBrush=new CBrush(RGB(255, 0, 0));
		}
		else if (myNode->strType == "Relay")
		{
			pBrush=new CBrush(RGB(0, 0, 255));
		}
		else if (myNode->strType == "Sink")
		{
			pBrush=new CBrush(RGB(0, 255, 0));
		}
		
		dc.SelectObject(pBrush);
		int nSize = 5;
		dc.Ellipse(myNode->nXPos-nSize, myNode->nYPos-nSize,myNode->nXPos+nSize, myNode->nYPos+nSize);
		
		// Draw the number of the node
		int xPos = myNode->nXPos+5;
		int yPos = myNode->nYPos-10;
		CString strID;
		strID.Format("%d", myNode->nNodeID);
		CFont font,*pOldFont;
		font.CreateFont(10, 6,20,0, 700,TRUE,FALSE,TRUE, ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
		pOldFont=dc.SelectObject(&font);
		dc.SetTextColor(RGB(255,0,0));
		dc.SetBkMode(TRANSPARENT);
		
		if (1)
		{
			dc.TextOut(xPos, yPos, strID);
		}

		m_nodeList.GetNext(pos);
	}
	

}

void CNetwork_Topology_GeneratorDlg::OnButtonGenerate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nodeList.RemoveAll();
	m_linkList.RemoveAll();
	// Seed
	srand(time(NULL)); 

	m_strOut = "";

	if (m_nNodeNum == 0)
	{
		MessageBox("Sorry, the total node number shouldn' be 0.");
		return;
	}
	if (m_nSinkNumber == 0)
	{
		MessageBox("Sorry, the number of Sink Node shouldn' be 0.");
		return;
	}



	int NN = m_nNodeNum;
	int NSink = m_nSinkNumber;

	UINT **Graph = new UINT*[NN];			// RemainM is the matrix after removing a vector.
	for(int j=0; j<NN; j++)
	{
		Graph[j] = new UINT[NN];
	}
	// Init

	while(1)
	{
		for (int i=0; i<NN; i++)
		{
			for (int j=0; j<NN; j++)
			{
				Graph[i][j] = 0;
			}
		}
		// Generate Graph Matrix.
		
		CString str;
		for (i=0; i<NN-m_nSinkNumber; i++)
		{
			for (j=i+1; j<NN; j++)
			{
				int nRand = rand()%2;
				Graph[i][j] = nRand;
				
			}
		}
		bool bNeedRegenerate = FALSE;
		for (j=1; j<NN; j++)
		{
			int nCnt = 0;
			for (i=0; i<NN-m_nSinkNumber; i++)
			{
				if (Graph[i][j] != 0)
				{
					nCnt++;
				}
			}
			if (nCnt == 0)
			{
				bNeedRegenerate = TRUE;
				break;
			}
		}
		if (bNeedRegenerate == FALSE)
		{
			break;
		}
	}
	

	

	// Finish Generating
	CString str;
	for (int i=0; i<NN; i++)
	{
		for (j=0; j<NN; j++)
		{
			str.Format("%d ", Graph[i][j]);
			m_strOut += str;			
		}
		m_strOut += "\r\n";
		
	}

	// Insert nodes into the two lists.

	for (i=1; i<= NN; i++)
	{
		CNode* pNode = new CNode;
		// Initialize
		pNode->nXPos = rand()%400 + 100;
		pNode->nYPos = rand()%400 + 100 ;
		pNode->nNodeID = i;
		if (i == 1)
		{
			pNode->strType = "Source";
			pNode->nXPos = 250;
			pNode->nYPos = 100;
		}
		else if (i<=NN && i>NN-m_nSinkNumber)
		{
			pNode->strType = "Sink";
			pNode->nYPos = 500;
		}
		else
		{
			pNode->strType = "Relay";
		}
	
		m_nodeList.AddTail((CObject *)pNode);
	}

/*	POSITION posStart = m_nodeList.GetHeadPosition();
	while (posStart != NULL)
	{
		CNode* pNodeStart = (CNode*)m_nodeList.GetAt(posStart);
		
		POSITION posEnd = m_nodeList.GetHeadPosition();
		while (posEnd != NULL)
		{
			CNode* pNodeEnd = (CNode*)m_nodeList.GetAt(posEnd);

			CPoint a, b;
			a.x= pNodeStart->nXPos;
			a.y = pNodeStart->nYPos;

			b.x = pNodeEnd->nXPos;
			b.y = pNodeEnd->nYPos;

			int nDistance = GetDistance(a, b);

			if (nDistance < 150 && b.y > a.y)
			{

				CLink* pLink = new CLink;
				pLink->posStartPos = a;
				pLink->posEndPos = b;
				m_linkList.AddTail((CObject *)pLink);
			}
			m_nodeList.GetNext(posEnd);
			
		}
		m_nodeList.GetNext(posStart);

	}
*/
	// Insert link in sequence.

	for (i=1; i<=NN; i++)
	{
		for (j=i+1; j<=NN; j++)
		{
			if (Graph[i-1][j-1] == 1)
			{
				// then, there is a link between i and j.
				CPoint posStart, posEnd;
				posStart.x = 0;
				posStart.y = 0;
				posEnd.x = 0;
				posEnd.y = 0;

				POSITION posStartNode = m_nodeList.GetHeadPosition();
				while(posStartNode != NULL)
				{
					CNode *pNode = (CNode*)m_nodeList.GetAt(posStartNode);
					
					if (pNode->nNodeID == i)
					{
						posStart.x = pNode->nXPos;
						posStart.y = pNode->nYPos;
						break;
					}
					m_nodeList.GetNext(posStartNode);
				}

				POSITION posEndNode = m_nodeList.GetHeadPosition();
				while(posEndNode != NULL)
				{
					CNode *pNode = (CNode*)m_nodeList.GetAt(posEndNode);
					
					if (pNode->nNodeID == j)
					{
						posEnd.x = pNode->nXPos;
						posEnd.y = pNode->nYPos;
						break;
					}
					m_nodeList.GetNext(posEndNode);
				}

				// Insert Link to LinkList;

				CLink* pLink = new CLink;
				pLink->posStartPos = posStart;
				pLink->posEndPos = posEnd;
				m_linkList.AddTail((CObject *)pLink);
				

			}
		}

	}

		
	
	

	for(i = 0; i < NN; i++) 
	{
		delete []Graph[i];
	}
	delete []Graph; 
	UpdateData(FALSE);
	InvalidateRect(FALSE);

}

void CNetwork_Topology_GeneratorDlg::OnBUTTONMoveNode() 
{
	// TODO: Add your control notification handler code here
	m_bAllowMoveNode = TRUE;
	m_bAllowDeleteNode = false;
	m_bAllowAddNode = FALSE;
	m_bAllowAddLink = FALSE;
	m_bAllowDeleteLink = FALSE;
}

int CNetwork_Topology_GeneratorDlg::GetDistance(CPoint posStart, CPoint posEnd)
{
	int x = abs(posStart.x - posEnd.x);
	int y = abs(posStart.y - posEnd.y);


	int z = sqrt(x*x + y*y);

	return z;
}

bool CNetwork_Topology_GeneratorDlg::DirectoryExist(CString str)
{		
		WIN32_FIND_DATA wfd; 	
		BOOL rValue = FALSE;  	
		HANDLE hFind = FindFirstFile(str, &wfd); 		
		if ((hFind!=INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)) 
		{  
			rValue = TRUE;		
		}  		
		FindClose(hFind); 	
		return rValue; 
}

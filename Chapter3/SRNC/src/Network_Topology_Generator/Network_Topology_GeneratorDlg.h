// Network_Topology_GeneratorDlg.h : header file
//

#if !defined(AFX_NETWORK_TOPOLOGY_GENERATORDLG_H__C2AC2995_854D_42E9_9935_9956C2CB95AA__INCLUDED_)
#define AFX_NETWORK_TOPOLOGY_GENERATORDLG_H__C2AC2995_854D_42E9_9935_9956C2CB95AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNetwork_Topology_GeneratorDlg dialog

class CNetwork_Topology_GeneratorDlg : public CDialog
{
// Construction
public:
	bool DirectoryExist(CString str);
	int GetDistance(CPoint posStart, CPoint posEnd);

	void DrawLinkAndNode();
	CNetwork_Topology_GeneratorDlg(CWnd* pParent = NULL);	// standard constructor

	void DrawArrow(CPoint p1,CPoint p2,double theta,int length);
	char m_szPath[254];
	bool m_bMoveNode;
	CPoint m_LatestPos;
	CPoint lastestPos;
	bool m_bAllowDeleteLink;
	bool m_bAllowDeleteNode;
	bool m_bAllowAddLink;
	bool m_bAllowAddNode;
	bool m_bAllowMoveNode;
	CObList m_nodeList;
	CObList m_linkList;

// Dialog Data
	//{{AFX_DATA(CNetwork_Topology_GeneratorDlg)
	enum { IDD = IDD_NETWORK_TOPOLOGY_GENERATOR_DIALOG };
	int		m_nRadio;
	CString	m_strOut;
	UINT	m_nNodeNum;
	UINT	m_nSinkNumber;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetwork_Topology_GeneratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNetwork_Topology_GeneratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONImport();
	afx_msg void OnBUTTONPlaceNode();
	afx_msg void OnBUTTONDeleteNode();
	afx_msg void OnBUTTONPlaceLink();
	afx_msg void OnBUTTONDeleteLink();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonSave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnButtonGenerate();
	afx_msg void OnBUTTONMoveNode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORK_TOPOLOGY_GENERATORDLG_H__C2AC2995_854D_42E9_9935_9956C2CB95AA__INCLUDED_)

// SRNC_ConstructorDlg.h : header file
//
#include "Link.h"

#if !defined(AFX_SRNC_CONSTRUCTORDLG_H__F843F1D8_CDB2_4C0C_AD7C_8BA0D2F2B264__INCLUDED_)
#define AFX_SRNC_CONSTRUCTORDLG_H__F843F1D8_CDB2_4C0C_AD7C_8BA0D2F2B264__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSRNC_ConstructorDlg dialog

class CSRNC_ConstructorDlg : public CDialog
{
// Construction
public:
	int m_nOrder;
	void GetOCV(UINT **RemianM, UINT *OCV, int nI);
	void UsingDeterministicAlgorithm();
	bool PreLinkAssigned(int nLinkNum);

	void UsingRandomAlgorithm();
	UINT m_nMulticastCapacity;
	void DrawArrow(CDC *pControlDC, CPoint p1, CPoint p2, double theta, int length);
	CSRNC_ConstructorDlg(CWnd* pParent = NULL);	// standard constructor

	CObList m_nodeList;
	CObList m_linkList;
	int m_nSrcID;

	CLink *m_pPreLink;		// Used to record the pointer of previous link such that copying GEVs is easy.


// Dialog Data
	//{{AFX_DATA(CSRNC_ConstructorDlg)
	enum { IDD = IDD_SRNC_CONSTRUCTOR_DIALOG };
	CString	m_strOutput;
	BOOL	m_bShowLinkNo;
	BOOL	m_bShowNodeNo;
	int		m_nAlgorithm;
	CString	m_strGCV;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRNC_ConstructorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSRNC_ConstructorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONImportTopo();
	afx_msg void OnBUTTONMaxflow();
	afx_msg void OnBUTTONAssignCode();
	afx_msg void OnCHECKLinkNum();
	afx_msg void OnCHECKNodeNum();
	afx_msg void OnRADIOalgorithm();
	afx_msg void OnRADIODalgorithm();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBUTTONCheck();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRNC_CONSTRUCTORDLG_H__F843F1D8_CDB2_4C0C_AD7C_8BA0D2F2B264__INCLUDED_)

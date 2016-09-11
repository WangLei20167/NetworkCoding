
// MatrixComputingDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMatrixComputingDlg dialog
class CMatrixComputingDlg : public CDialogEx
{
// Construction
public:
	CMatrixComputingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MATRIXCOMPUTING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	int m_Matrix;
//	int m_Matrix2;
//	int m_Matrix3;
	afx_msg void OnBnClickedButton2();
//	int nOperation;
	void compute();
	afx_msg void OnBnClickedTranspose();
	afx_msg void OnBnClickedInverse();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedMultiply();
	afx_msg void OnEnChangeOrder();
	int m_nOrder;
	afx_msg void OnEnChangeEditleft();
	CFont m_Font;
	CEdit m_Matrix;
	CEdit m_Matrix2;
	CEdit m_Matrix3;
	int nOperation;
};

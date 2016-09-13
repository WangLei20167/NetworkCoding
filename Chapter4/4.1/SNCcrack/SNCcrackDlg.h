
// SNCcrackDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CSNCcrackDlg 对话框
class CSNCcrackDlg : public CDialogEx
{
// 构造
public:
	CSNCcrackDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SNCCRACK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	UINT m_nM;
	CEdit m_Matrix;
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonBruteforce();
//	long factorial(int n);
//	void BruteForce();
//	void BruthForce(int** M, int nRow, int nCol);
//	void BruteForce(int& M, int nRow, int nCol);
//	void BruteForce(int* & M, int nRow, int nCol);
//	void Bruth(int** & M, int nRow, int nCol);
//	void BruteForce(const int** & M, int nRow, int nCol);
//	void BruteForce(const int** G, int nRow, int nCol);
//	void BruteForce(int** G, int nRow, int nCol);
//	bool BruteForce(int** G, int nRow, int nCol);
//	bool vectorComb(int** G, int nRow, int nCol);
//	bool vectorComb(int** G, int nRow, int nCol, int** matrix, int nTotal, int nCur, int i);
	bool BruteForce(int** G, int nRow, int nCol);
//	bool vectorComb(int** G, int nRow, int nCol, int** & matrix, int nTotal, int nCur, int i);
//	bool vectorComb(int** G, int nRow, int nCol, int** matrix, int nTotal, int nCur, int i);
};

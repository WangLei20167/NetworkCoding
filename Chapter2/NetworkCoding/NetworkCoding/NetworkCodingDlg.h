
// NetworkCodingDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CNetworkCodingDlg 对话框
class CNetworkCodingDlg : public CDialogEx
{
// 构造
public:
	CNetworkCodingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETWORKCODING_DIALOG };

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
	afx_msg void OnBnClickedSelect();
	int K;
	int N;
	CString g_filePath;

	afx_msg void OnBnClickedCode();
	byte** Multiply(byte** matA, byte** matB, int nRow, int n, int nCol);
	afx_msg void OnBnClickedRecovery();
	byte** Inverse(byte** G, int n);
	int g_flag = 0;
	afx_msg void OnBnClickedOpendirectory();
	
	afx_msg void OnBnClickedClear();
//	CString m_szProgress;
	afx_msg void OnEnChangeProgress();
//	CString m_szProg;
	CString Step_info;
	afx_msg void OnBnClickedRecode();
//	CEdit Scroll;
//	void OutputWithScroll(const CString& strNewText, CEdit & edtOutput);
//	CEdit* pedit;
//	void stepInfo();
	void Scroll();
	CString g_extName;
};

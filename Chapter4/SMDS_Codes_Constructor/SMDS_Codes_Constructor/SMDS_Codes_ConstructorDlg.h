
// SMDS_Codes_ConstructorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CSMDS_Codes_ConstructorDlg 对话框
class CSMDS_Codes_ConstructorDlg : public CDialogEx
{
// 构造
public:
	CSMDS_Codes_ConstructorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SMDS_CODES_CONSTRUCTOR_DIALOG };

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

	CFont m_Font;
	CString m_strValue1;
	CString m_strValue2;

	UINT m_nK1;
	UINT m_nK2;
	UINT m_nOrder;
	UINT m_nN1;
	UINT m_nN2;

	CString m_strMaxN2;

	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEditArea1();
	afx_msg void OnEnChangeEditArea2();
	afx_msg void OnEnChangeEditArea3();
	afx_msg void OnBnClickedButtonGetMdsCode();
	afx_msg void OnBnClickedButtonGetSmdsCode();
	afx_msg void OnBnClickedButtonEvaluate();
	afx_msg void OnBnClickedButtonReport();

	CEdit m_AREA1;
	CEdit m_AREA2;
	afx_msg void OnEnChangeEditM();

	CString m_strMaxN1;
	UINT m_nK3;
	UINT m_nN3;
	afx_msg void OnBnClickedButtonReport2();
	afx_msg void OnBnClickedButtonRandom();
	CEdit m_AREA3;
	afx_msg void OnStnClickedStaticSecurity();
};

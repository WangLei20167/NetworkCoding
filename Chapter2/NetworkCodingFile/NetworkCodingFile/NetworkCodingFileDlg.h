
// NetworkCodingFileDlg.h : 头文件
//

#pragma once


// CNetworkCodingFileDlg 对话框
class CNetworkCodingFileDlg : public CDialogEx
{
// 构造
public:
	CNetworkCodingFileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETWORKCODINGFILE_DIALOG };

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
	int K;
	int N;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedEncode();
	afx_msg void OnBnClickedReencode();
	afx_msg void OnBnClickedRecover();
	afx_msg void OnBnClickedBrowse();
//	afx_msg void OnBnClickedClear();
	CString g_filePath;
	int g_flag=0;
	CString g_extName;
	CString Step_info;
	byte** Inverse(byte** G, int n);
	byte** Multiply(byte** matA, byte** matB, int nRow, int n, int nCol);
	void Scroll();
	void PostNcDestroy();
	void DeleteFiles();
	afx_msg void OnBnClickedDownload();
};

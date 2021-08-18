
// EverythingProDlg.h: 头文件
//

#pragma once
#include"Search.h"

// CEverythingProDlg 对话框
class CEverythingProDlg : public CDialogEx
{
// 构造
public:
	CEverythingProDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVERYTHINGPRO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	Search mSearch;
	SearchParams mParams;
	vector<WeChatResult> VweChat;
	std::vector<SearchResult> VAllResult;
	char mSavePath[MAX_PATH];
	bool bThreadRun;
	void ShowInfo(const char* format, ...);
	CWinThread* m_pInspectThread;
	DWORD dwExitCode;
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
	afx_msg void OnBnClickedButtonSearch();
	CStatic m_Static_path;
	afx_msg void OnBnClickedButtonSelectpath();
	afx_msg void OnBnClickedButtonSearch2();
	CListBox m_listBox;
	CStatic m_Static_Info;
	CButton m_btnSearch;
	CButton m_btnStop;
	afx_msg void OnBnClickedButtonStop();
	CButton m_btncopy;
	afx_msg void OnBnClickedButtonCopy();
};

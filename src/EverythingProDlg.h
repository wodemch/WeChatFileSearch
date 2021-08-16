
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
private:
	Search mSearch;
	SearchParams mParams;
	std::vector<SearchResult> VAllResult;

	void SetListText(int index, std::string name, std::string path, LONGLONG size);

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
	afx_msg void OnEnChangeEditSearch();
	CString m_str_Search;
	CString m_str_Exclude;
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButtonSearch();
	CTreeCtrl m_Tree;
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
};

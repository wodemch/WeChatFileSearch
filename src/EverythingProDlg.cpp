
// EverythingProDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "EverythingPro.h"
#include "EverythingProDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEverythingProDlg 对话框



CEverythingProDlg::CEverythingProDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EVERYTHINGPRO_DIALOG, pParent)
	, m_str_Search(_T(""))
	, m_str_Exclude(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEverythingProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Search, m_str_Search);
	DDX_Text(pDX, IDC_EDIT2, m_str_Exclude);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
}

BEGIN_MESSAGE_MAP(CEverythingProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_Search, &CEverythingProDlg::OnEnChangeEditSearch)
	ON_BN_CLICKED(IDC_BUTTON_Search, &CEverythingProDlg::OnBnClickedButtonSearch)
	ON_WM_KEYDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CEverythingProDlg::OnNMDblclkTree1)
END_MESSAGE_MAP()


// CEverythingProDlg 消息处理程序

BOOL CEverythingProDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	

	// TODO: 在此添加额外的初始化代码
	m_ListCtrl.InsertColumn(0, _T("名称"), LVCFMT_LEFT, 255);
	m_ListCtrl.InsertColumn(1, _T("路径"), LVCFMT_LEFT, 500);
	m_ListCtrl.InsertColumn(2, _T("大小"), LVCFMT_LEFT, 270);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEverythingProDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEverythingProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEverythingProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEverythingProDlg::SetListText(int index, std::string name, std::string path, LONGLONG size)
{
	m_ListCtrl.InsertItem(index, name.c_str());    
	m_ListCtrl.SetItemText(index, 1, path.c_str()); 
	//m_ListCtrl.SetItemText(index, 2, itoa(size));
}

void CEverythingProDlg::OnEnChangeEditSearch()
{
	
}


void CEverythingProDlg::OnBnClickedButtonSearch()
{
	UpdateData(true);
	sprintf_s(mParams.searchStr, MAX_SEARCH_LENGHT, m_str_Search.GetBuffer());
	sprintf_s(mParams.excludeStr, MAX_SEARCH_LENGHT, m_str_Exclude.GetBuffer());

	vector<WeChatResult> VweChat = mSearch.SearchExe();
	for each(WeChatResult obj in VweChat) 
	{
		HTREEITEM root = m_Tree.InsertItem(obj.UserName.c_str());
		HTREEITEM FileTree = m_Tree.InsertItem("File",root);
		for each(PathInfo info in obj.vFilePath)
		{
			m_Tree.InsertItem(info.FileName.c_str(), FileTree);
		}
		HTREEITEM ImageTree = m_Tree.InsertItem("Image", root);
		for each(PathInfo info in obj.vImagePath)
		{
			m_Tree.InsertItem(info.FileName.c_str(), ImageTree);
		}
		HTREEITEM VideoTree = m_Tree.InsertItem("Video", root);
		for each(PathInfo info in obj.vVideoPath)
		{
			m_Tree.InsertItem(info.FileName.c_str(), VideoTree);
		}
	}
	
	return;
	VAllResult = mSearch.SearchExe(mParams);
	m_ListCtrl.DeleteAllItems();
	int maxNum = min(100, VAllResult.size());
	for (size_t i = 0; i < maxNum; i++)
	{
		SetListText(i, VAllResult.at(i).Name, VAllResult.at(i).Path, VAllResult.at(i).size.QuadPart);
	}
}

BOOL CEverythingProDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedButtonSearch();
		return TRUE;
	}
	else
		return CDialog::PreTranslateMessage(pMsg);
}


void CEverythingProDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

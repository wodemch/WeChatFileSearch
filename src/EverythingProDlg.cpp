
// EverythingProDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "EverythingPro.h"
#include "EverythingProDlg.h"
#include "afxdialogex.h"

#include"./mtgh/MtghWindow.h"

#ifdef _WIN64
#pragma comment(lib, "./mtgh/MtghWindow_x64.lib")
#else
#pragma comment(lib, "./mtgh/MtghWindow_Win32.lib")
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


UINT StartSearchPro(LPVOID lpParam)
{
	CEverythingProDlg* pAL = (CEverythingProDlg*)lpParam;
	pAL->bThreadRun = true;	
	string newRootPath = pAL->mSavePath;
	for each(WeChatResult obj in pAL->VweChat)
	{
		string newfile = newRootPath + "\\" + obj.UserName;
		//MT_CopyFile(obj.RootPath.c_str(), newfile.c_str());

		string path = newfile + "\\File";
		int index = 0;
		for each (PathInfo varP in obj.vFilePath)
		{
			if (pAL->bThreadRun == false)break;
			string file = path + "\\" + varP.FileName;
			MT_CopyFile(varP.Path.c_str(), file.c_str(), true);
			pAL->ShowInfo("username:%s, File:%d-%d,%s", obj.UserName, ++index, obj.vFilePath.size(), file.c_str());
		}
		index = 0;
		path = newfile + "\\Image";
		for each (PathInfo varP in obj.vImagePath)
		{
			if (pAL->bThreadRun == false)break;
			string file = path + "\\" + varP.FileName;
			MT_CopyFile(varP.Path.c_str(), file.c_str(), true);
			pAL->ShowInfo("username:%s, Image:%d-%d,%s", obj.UserName, ++index, obj.vImagePath.size(), file.c_str());
		}
		index = 0;
		path = newfile + "\\Video";
		for each (PathInfo varP in obj.vVideoPath)
		{
			if (pAL->bThreadRun == false)break;
			string file = path + "\\" + varP.FileName;
			MT_CopyFile(varP.Path.c_str(), file.c_str(), true);
			pAL->ShowInfo("username:%s, Video:%d-%d,%s", obj.UserName, ++index, obj.vVideoPath.size(), file.c_str());
		}
	}
	pAL->bThreadRun = false;
	return 0;
}

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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEverythingProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PATH, m_Static_path);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Control(pDX, IDC_STATIC_INFO, m_Static_Info);
	DDX_Control(pDX, IDC_BUTTON_Search, m_btnSearch);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BUTTON_Copy, m_btncopy);
}

BEGIN_MESSAGE_MAP(CEverythingProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Search, &CEverythingProDlg::OnBnClickedButtonSearch)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON_SELECTPATH, &CEverythingProDlg::OnBnClickedButtonSelectpath)
	ON_BN_CLICKED(IDC_BUTTON_Search2, &CEverythingProDlg::OnBnClickedButtonSearch2)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CEverythingProDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_Copy, &CEverythingProDlg::OnBnClickedButtonCopy)
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
	
	sprintf_s(mSavePath, MAX_PATH, "E:\\111");
	bThreadRun = false;
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

void CEverythingProDlg::ShowInfo(const char* format, ...)
{
	char buf[1024] = "";
	va_list arg;
	va_start(arg, format);
	vsprintf_s(buf,1024, format, arg);
	va_end(arg);
	m_Static_Info.SetWindowTextA(buf);
}

void CEverythingProDlg::OnBnClickedButtonSearch()
{
	if (bThreadRun) {
		AfxMessageBox("请等待等待上一次搜索结束", MB_ICONWARNING);
	}
	else {
		VweChat.clear();
		VweChat = mSearch.SearchExe();
		char buf[256] = "";
		m_listBox.ResetContent();
		for each(WeChatResult obj in VweChat)
		{
			sprintf_s(buf, 512, "%s: File:%d, Image:%d, Video:%d", obj.UserName.c_str(),
				obj.vFilePath.size(), obj.vImagePath.size(), obj.vVideoPath.size());
			m_listBox.AddString(buf);
		}			
	}	
}

void CEverythingProDlg::OnBnClickedButtonCopy()
{
	if (bThreadRun) {
		AfxMessageBox("请等待等待上一次拷贝结束", MB_ICONWARNING);
	}
	else {
		m_btncopy.EnableWindow(false);
		m_btnStop.EnableWindow(true);
		m_pInspectThread = AfxBeginThread(StartSearchPro, (LPVOID)this);
	}
}

void CEverythingProDlg::OnBnClickedButtonStop()
{
	bThreadRun = false;
	m_btncopy.EnableWindow(true);
	m_btnStop.EnableWindow(false);
}

BOOL CEverythingProDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CEverythingProDlg::OnBnClickedButtonSelectpath()
{
	string path;
	if (MT_SelectFolder(path))
	{
		sprintf_s(mSavePath, "%s", path.c_str());
		m_Static_path.SetWindowTextA(mSavePath);
	}
}

void CEverythingProDlg::OnBnClickedButtonSearch2()
{
	MT_CmdOrder(CT_OPEN, mSavePath);
}





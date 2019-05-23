
// GDSFileToBMPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GDSFileToBMP.h"
#include "GDSFileToBMPDlg.h"
#include "GdsParserToBMP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGDSFileToBMPDlg 对话框

StruParseFileInfo CGDSFileToBMPDlg::m_stuFilrInfo;


CGDSFileToBMPDlg::CGDSFileToBMPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGDSFileToBMPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGDSFileToBMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_ANALY, m_ctrlProgress);
	DDX_Control(pDX, IDC_STATIC_PROGRESS_PROMT, m_statPromt);
}

BEGIN_MESSAGE_MAP(CGDSFileToBMPDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGDSFileToBMPDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGDSFileToBMPDlg 消息处理程序

BOOL CGDSFileToBMPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGDSFileToBMPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGDSFileToBMPDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGDSFileToBMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGDSFileToBMPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, _T("Describe Files (*.gds)|*.gds||"), NULL);
	//最多可以打开500个文件  
	dlgFile.m_ofn.nMaxFile = 500 * MAX_PATH;  
	m_stuFilrInfo.m_strAryFilePath.RemoveAll();
	m_stuFilrInfo.m_pctrlProgress = &m_ctrlProgress;
	m_stuFilrInfo.m_pstatPromt = &m_statPromt;

	TCHAR* ch = new TCHAR[dlgFile.m_ofn.nMaxFile];  
	dlgFile.m_ofn.lpstrFile = ch;  
	//对内存块清零  
	ZeroMemory(dlgFile.m_ofn.lpstrFile,sizeof(TCHAR) * dlgFile.m_ofn.nMaxFile); 
	CString pathName,fileName,fileTitle;  
	if (dlgFile.DoModal() == IDOK)
	{
		//获取第一个文件的位置  
		POSITION pos_file;  
		pos_file = dlgFile.GetStartPosition();  

		//循环读出每个路径并存放在数组中  
		while(pos_file != NULL)
		{  

			//将文件路径存放在数组中  
			pathName = dlgFile.GetNextPathName(pos_file);  

			m_stuFilrInfo.m_strAryFilePath.Add(pathName);
		}

		AfxBeginThread(ParseGdsFileThreadProc,&m_stuFilrInfo, THREAD_PRIORITY_NORMAL);

	}
	delete[] ch;  

//	OnOK();
}

UINT CGDSFileToBMPDlg::ParseGdsFileThreadProc( LPVOID pParam )
{
	StruParseFileInfo * pStuMarkData = (StruParseFileInfo * )pParam;
	if(pStuMarkData == NULL)
	{
		return 0;
	}
	// 复制一个临时的对象，避免对话框退出导致指正无效
	//StruParseFileInfo procStuMark = *pStuMarkData;

	// 处理替换文字
	for(int i = 0; i < pStuMarkData->m_strAryFilePath.GetCount(); i++)  
	{
		CString strFileName = pStuMarkData->m_strAryFilePath.GetAt(i);
		strFileName = strFileName.Mid(strFileName.ReverseFind('\\') + 1 );
		CString strTitle;
		strTitle.Format(_T("正在解析文件%s……"), strFileName);
		pStuMarkData->m_pstatPromt->SetWindowText(strTitle);
		GdsParserToBMP parser(m_stuFilrInfo.m_pctrlProgress);
		parser.parse(pStuMarkData->m_strAryFilePath.GetAt(i));
		//parser.PrintExtentPoint();
		strTitle.Format(_T("正在将文件%s的解析数据保存为BMP……"), strFileName);
		pStuMarkData->m_pstatPromt->SetWindowText(strTitle);
		parser.TransPointToPixel();
	}

	pStuMarkData->m_pstatPromt->SetWindowText(_T("解析转换完成"));
}

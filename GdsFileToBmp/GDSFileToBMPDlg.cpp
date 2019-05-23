
// GDSFileToBMPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GDSFileToBMP.h"
#include "GDSFileToBMPDlg.h"
#include "GdsParserToBMP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGDSFileToBMPDlg �Ի���

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


// CGDSFileToBMPDlg ��Ϣ�������

BOOL CGDSFileToBMPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGDSFileToBMPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGDSFileToBMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGDSFileToBMPDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, _T("Describe Files (*.gds)|*.gds||"), NULL);
	//�����Դ�500���ļ�  
	dlgFile.m_ofn.nMaxFile = 500 * MAX_PATH;  
	m_stuFilrInfo.m_strAryFilePath.RemoveAll();
	m_stuFilrInfo.m_pctrlProgress = &m_ctrlProgress;
	m_stuFilrInfo.m_pstatPromt = &m_statPromt;

	TCHAR* ch = new TCHAR[dlgFile.m_ofn.nMaxFile];  
	dlgFile.m_ofn.lpstrFile = ch;  
	//���ڴ������  
	ZeroMemory(dlgFile.m_ofn.lpstrFile,sizeof(TCHAR) * dlgFile.m_ofn.nMaxFile); 
	CString pathName,fileName,fileTitle;  
	if (dlgFile.DoModal() == IDOK)
	{
		//��ȡ��һ���ļ���λ��  
		POSITION pos_file;  
		pos_file = dlgFile.GetStartPosition();  

		//ѭ������ÿ��·���������������  
		while(pos_file != NULL)
		{  

			//���ļ�·�������������  
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
	// ����һ����ʱ�Ķ��󣬱���Ի����˳�����ָ����Ч
	//StruParseFileInfo procStuMark = *pStuMarkData;

	// �����滻����
	for(int i = 0; i < pStuMarkData->m_strAryFilePath.GetCount(); i++)  
	{
		CString strFileName = pStuMarkData->m_strAryFilePath.GetAt(i);
		strFileName = strFileName.Mid(strFileName.ReverseFind('\\') + 1 );
		CString strTitle;
		strTitle.Format(_T("���ڽ����ļ�%s����"), strFileName);
		pStuMarkData->m_pstatPromt->SetWindowText(strTitle);
		GdsParserToBMP parser(m_stuFilrInfo.m_pctrlProgress);
		parser.parse(pStuMarkData->m_strAryFilePath.GetAt(i));
		//parser.PrintExtentPoint();
		strTitle.Format(_T("���ڽ��ļ�%s�Ľ������ݱ���ΪBMP����"), strFileName);
		pStuMarkData->m_pstatPromt->SetWindowText(strTitle);
		parser.TransPointToPixel();
	}

	pStuMarkData->m_pstatPromt->SetWindowText(_T("����ת�����"));
}

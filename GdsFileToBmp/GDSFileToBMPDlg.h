
// GDSFileToBMPDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

typedef struct _StruParseFileInfo 
{
	CStringArray m_strAryFilePath;
	CProgressCtrl* m_pctrlProgress;
	CStatic* m_pstatPromt;
}StruParseFileInfo;

// CGDSFileToBMPDlg �Ի���
class CGDSFileToBMPDlg : public CDialog
{
// ����
public:
	CGDSFileToBMPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GDSFILETOBMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	static UINT ParseGdsFileThreadProc( LPVOID pParam );
	static StruParseFileInfo m_stuFilrInfo;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CProgressCtrl m_ctrlProgress;
	CStatic m_statPromt;
};

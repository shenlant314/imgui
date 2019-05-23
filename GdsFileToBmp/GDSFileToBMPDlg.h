
// GDSFileToBMPDlg.h : 头文件
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

// CGDSFileToBMPDlg 对话框
class CGDSFileToBMPDlg : public CDialog
{
// 构造
public:
	CGDSFileToBMPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GDSFILETOBMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	static UINT ParseGdsFileThreadProc( LPVOID pParam );
	static StruParseFileInfo m_stuFilrInfo;

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
	afx_msg void OnBnClickedOk();
	CProgressCtrl m_ctrlProgress;
	CStatic m_statPromt;
};

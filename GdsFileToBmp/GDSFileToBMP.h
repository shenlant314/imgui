
// GDSFileToBMP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGDSFileToBMPApp:
// �йش����ʵ�֣������ GDSFileToBMP.cpp
//

class CGDSFileToBMPApp : public CWinAppEx
{
public:
	CGDSFileToBMPApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGDSFileToBMPApp theApp;
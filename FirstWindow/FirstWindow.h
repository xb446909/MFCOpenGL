
// FirstWindow.h : FirstWindow Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CFirstWindowApp:
// �йش����ʵ�֣������ FirstWindow.cpp
//

class CFirstWindowApp : public CWinAppEx
{
public:
	CFirstWindowApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFirstWindowApp theApp;

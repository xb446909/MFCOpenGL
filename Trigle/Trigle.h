
// Trigle.h : Trigle Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTrigleApp:
// �йش����ʵ�֣������ Trigle.cpp
//

class CTrigleApp : public CWinAppEx
{
public:
	CTrigleApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTrigleApp theApp;
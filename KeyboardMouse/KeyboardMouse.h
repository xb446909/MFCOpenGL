
// KeyboardMouse.h : KeyboardMouse Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CKeyboardMouseApp:
// �йش����ʵ�֣������ KeyboardMouse.cpp
//

class CKeyboardMouseApp : public CWinAppEx
{
public:
	CKeyboardMouseApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKeyboardMouseApp theApp;

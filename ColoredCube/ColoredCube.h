
// ColoredCube.h : ColoredCube Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CColoredCubeApp:
// �йش����ʵ�֣������ ColoredCube.cpp
//

class CColoredCubeApp : public CWinAppEx
{
public:
	CColoredCubeApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CColoredCubeApp theApp;


// TexturedCube.h : TexturedCube Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTexturedCubeApp:
// �йش����ʵ�֣������ TexturedCube.cpp
//

class CTexturedCubeApp : public CWinAppEx
{
public:
	CTexturedCubeApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTexturedCubeApp theApp;
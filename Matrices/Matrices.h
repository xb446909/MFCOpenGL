
// Matrices.h : Matrices Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMatricesApp:
// �йش����ʵ�֣������ Matrices.cpp
//

class CMatricesApp : public CWinAppEx
{
public:
	CMatricesApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMatricesApp theApp;


// TrigleView.h : CTrigleView ��Ľӿ�
//

#pragma once

#include "../GL/include/glew.h"
#include <gl/GLU.h>


class CTrigleView : public CView
{
protected: // �������л�����
	CTrigleView();
	DECLARE_DYNCREATE(CTrigleView)

// ����
public:
	CTrigleDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	CDC* m_pDC;
	int m_nWidth;
	int m_nHeight;
	GLuint m_programID;
	GLuint m_vertexArrayID;
	GLuint m_vertexbuffer;

	BOOL SetupPixelFormat(HDC hDC);
	BOOL InitOpenGL(HDC hDC);
	void RenderScene();

// ʵ��
public:
	virtual ~CTrigleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // TrigleView.cpp �еĵ��԰汾
inline CTrigleDoc* CTrigleView::GetDocument() const
   { return reinterpret_cast<CTrigleDoc*>(m_pDocument); }
#endif


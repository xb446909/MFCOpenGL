
// FirstWindowView.h : CFirstWindowView ��Ľӿ�
//

#pragma once

#include "../GL/include/glew.h"
#include <gl/GLU.h>

class CFirstWindowView : public CView
{
protected: // �������л�����
	CFirstWindowView();
	DECLARE_DYNCREATE(CFirstWindowView)

// ����
public:
	CFirstWindowDoc* GetDocument() const;

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

// ʵ��
public:
	virtual ~CFirstWindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

private:
	CDC* m_pDC;
	int m_nWidth;
	int m_nHeight;
	GLuint programID;
	GLuint VertexArrayID;
	GLuint vertexbuffer;

	BOOL SetupPixelFormat(HDC hDC);
	BOOL InitOpenGL(HDC hDC);
	void RenderScene();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // FirstWindowView.cpp �еĵ��԰汾
inline CFirstWindowDoc* CFirstWindowView::GetDocument() const
   { return reinterpret_cast<CFirstWindowDoc*>(m_pDocument); }
#endif


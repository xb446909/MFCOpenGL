
// ColoredCubeView.h : CColoredCubeView ��Ľӿ�
//

#pragma once
#include "OpenGL.h"

class CColoredCubeView : public CView
{
protected: // �������л�����
	CColoredCubeView();
	DECLARE_DYNCREATE(CColoredCubeView)

// ����
public:
	CColoredCubeDoc* GetDocument() const;

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
	COpenGL m_opengl;

// ʵ��
public:
	virtual ~CColoredCubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // ColoredCubeView.cpp �еĵ��԰汾
inline CColoredCubeDoc* CColoredCubeView::GetDocument() const
   { return reinterpret_cast<CColoredCubeDoc*>(m_pDocument); }
#endif


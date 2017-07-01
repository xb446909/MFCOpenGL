
// MatricesView.h : CMatricesView ��Ľӿ�
//

#pragma once

#include "OpenGL.h"

class CMatricesView : public CView
{
protected: // �������л�����
	CMatricesView();
	DECLARE_DYNCREATE(CMatricesView)

// ����
public:
	CMatricesDoc* GetDocument() const;

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
	virtual ~CMatricesView();
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

#ifndef _DEBUG  // MatricesView.cpp �еĵ��԰汾
inline CMatricesDoc* CMatricesView::GetDocument() const
   { return reinterpret_cast<CMatricesDoc*>(m_pDocument); }
#endif


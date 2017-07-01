
// MatricesView.h : CMatricesView 类的接口
//

#pragma once

#include "OpenGL.h"

class CMatricesView : public CView
{
protected: // 仅从序列化创建
	CMatricesView();
	DECLARE_DYNCREATE(CMatricesView)

// 特性
public:
	CMatricesDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	CDC* m_pDC;
	COpenGL m_opengl;

// 实现
public:
	virtual ~CMatricesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // MatricesView.cpp 中的调试版本
inline CMatricesDoc* CMatricesView::GetDocument() const
   { return reinterpret_cast<CMatricesDoc*>(m_pDocument); }
#endif


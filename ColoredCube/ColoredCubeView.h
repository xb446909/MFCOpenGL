
// ColoredCubeView.h : CColoredCubeView 类的接口
//

#pragma once
#include "OpenGL.h"

class CColoredCubeView : public CView
{
protected: // 仅从序列化创建
	CColoredCubeView();
	DECLARE_DYNCREATE(CColoredCubeView)

// 特性
public:
	CColoredCubeDoc* GetDocument() const;

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
	virtual ~CColoredCubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // ColoredCubeView.cpp 中的调试版本
inline CColoredCubeDoc* CColoredCubeView::GetDocument() const
   { return reinterpret_cast<CColoredCubeDoc*>(m_pDocument); }
#endif


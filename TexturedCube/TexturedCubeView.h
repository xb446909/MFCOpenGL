
// TexturedCubeView.h : CTexturedCubeView 类的接口
//

#pragma once
#include "OpenGL.h"

class CTexturedCubeView : public CView
{
protected: // 仅从序列化创建
	CTexturedCubeView();
	DECLARE_DYNCREATE(CTexturedCubeView)

// 特性
public:
	CTexturedCubeDoc* GetDocument() const;

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
	CDC* m_pDC;	COpenGL m_opengl;
// 实现
public:
	virtual ~CTexturedCubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	afx_msg void OnDestroy();	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	afx_msg void OnSize(UINT nType, int cx, int cy);};

#ifndef _DEBUG  // TexturedCubeView.cpp 中的调试版本
inline CTexturedCubeDoc* CTexturedCubeView::GetDocument() const
   { return reinterpret_cast<CTexturedCubeDoc*>(m_pDocument); }
#endif


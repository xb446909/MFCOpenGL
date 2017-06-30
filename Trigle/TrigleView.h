
// TrigleView.h : CTrigleView 类的接口
//

#pragma once

#include "../GL/include/glew.h"
#include <gl/GLU.h>


class CTrigleView : public CView
{
protected: // 仅从序列化创建
	CTrigleView();
	DECLARE_DYNCREATE(CTrigleView)

// 特性
public:
	CTrigleDoc* GetDocument() const;

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
	int m_nWidth;
	int m_nHeight;
	GLuint m_programID;
	GLuint m_vertexArrayID;
	GLuint m_vertexbuffer;

	BOOL SetupPixelFormat(HDC hDC);
	BOOL InitOpenGL(HDC hDC);
	void RenderScene();

// 实现
public:
	virtual ~CTrigleView();
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

#ifndef _DEBUG  // TrigleView.cpp 中的调试版本
inline CTrigleDoc* CTrigleView::GetDocument() const
   { return reinterpret_cast<CTrigleDoc*>(m_pDocument); }
#endif


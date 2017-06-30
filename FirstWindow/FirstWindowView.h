
// FirstWindowView.h : CFirstWindowView 类的接口
//

#pragma once

#include "../GL/include/glew.h"
#include <gl/GLU.h>

class CFirstWindowView : public CView
{
protected: // 仅从序列化创建
	CFirstWindowView();
	DECLARE_DYNCREATE(CFirstWindowView)

// 特性
public:
	CFirstWindowDoc* GetDocument() const;

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

// 实现
public:
	virtual ~CFirstWindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // FirstWindowView.cpp 中的调试版本
inline CFirstWindowDoc* CFirstWindowView::GetDocument() const
   { return reinterpret_cast<CFirstWindowDoc*>(m_pDocument); }
#endif


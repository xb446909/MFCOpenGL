
// KeyboardMouseView.h : CKeyboardMouseView ��Ľӿ�
//

#pragma once
#include "OpenGL.h"

class CKeyboardMouseView : public COpenGL
{
protected: // �������л�����
	CKeyboardMouseView();
	DECLARE_DYNCREATE(CKeyboardMouseView)

// ����
public:
	CKeyboardMouseDoc* GetDocument() const;

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
	virtual ~CKeyboardMouseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // KeyboardMouseView.cpp �еĵ��԰汾
inline CKeyboardMouseDoc* CKeyboardMouseView::GetDocument() const
   { return reinterpret_cast<CKeyboardMouseDoc*>(m_pDocument); }
#endif


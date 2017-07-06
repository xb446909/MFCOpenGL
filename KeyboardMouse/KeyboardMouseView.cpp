
// KeyboardMouseView.cpp : CKeyboardMouseView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KeyboardMouse.h"
#endif

#include "KeyboardMouseDoc.h"
#include "KeyboardMouseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyboardMouseView

IMPLEMENT_DYNCREATE(CKeyboardMouseView, COpenGL)

BEGIN_MESSAGE_MAP(CKeyboardMouseView, COpenGL)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CKeyboardMouseView 构造/析构

CKeyboardMouseView::CKeyboardMouseView()
{
	// TODO: 在此处添加构造代码

}

CKeyboardMouseView::~CKeyboardMouseView()
{
}

BOOL CKeyboardMouseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CKeyboardMouseView 绘制

void CKeyboardMouseView::OnDraw(CDC* /*pDC*/)
{
	CKeyboardMouseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	RenderScene();
}


// CKeyboardMouseView 打印

BOOL CKeyboardMouseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CKeyboardMouseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CKeyboardMouseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CKeyboardMouseView 诊断

#ifdef _DEBUG
void CKeyboardMouseView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyboardMouseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyboardMouseDoc* CKeyboardMouseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyboardMouseDoc)));
	return (CKeyboardMouseDoc*)m_pDocument;
}
#endif //_DEBUG


// CKeyboardMouseView 消息处理程序

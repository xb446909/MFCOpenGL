
// ColoredCubeView.cpp : CColoredCubeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ColoredCube.h"
#endif

#include "ColoredCubeDoc.h"
#include "ColoredCubeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColoredCubeView

IMPLEMENT_DYNCREATE(CColoredCubeView, CView)

BEGIN_MESSAGE_MAP(CColoredCubeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CColoredCubeView 构造/析构

CColoredCubeView::CColoredCubeView()
{
	// TODO: 在此处添加构造代码

}

CColoredCubeView::~CColoredCubeView()
{
}

BOOL CColoredCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CColoredCubeView 绘制

void CColoredCubeView::OnDraw(CDC* /*pDC*/)
{
	CColoredCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CColoredCubeView 打印

BOOL CColoredCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CColoredCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CColoredCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CColoredCubeView 诊断

#ifdef _DEBUG
void CColoredCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CColoredCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColoredCubeDoc* CColoredCubeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColoredCubeDoc)));
	return (CColoredCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CColoredCubeView 消息处理程序

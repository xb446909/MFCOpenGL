
// MatricesView.cpp : CMatricesView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Matrices.h"
#endif

#include "MatricesDoc.h"
#include "MatricesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMatricesView

IMPLEMENT_DYNCREATE(CMatricesView, CView)

BEGIN_MESSAGE_MAP(CMatricesView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMatricesView 构造/析构

CMatricesView::CMatricesView()
{
	// TODO: 在此处添加构造代码

}


CMatricesView::~CMatricesView()
{
}

BOOL CMatricesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMatricesView 绘制

void CMatricesView::OnDraw(CDC* /*pDC*/)
{
	CMatricesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	m_opengl.RenderScene();
}


// CMatricesView 打印

BOOL CMatricesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMatricesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMatricesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMatricesView 诊断

#ifdef _DEBUG
void CMatricesView::AssertValid() const
{
	CView::AssertValid();
}

void CMatricesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

int CMatricesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);
	m_opengl.SetHDC(m_pDC->GetSafeHdc());
	if (!m_opengl.init())
		MessageBox(_T("Init opengl error"));

	return 0;
}

void CMatricesView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	if (m_pDC != NULL)
		delete m_pDC;
	m_pDC = NULL;
}

BOOL CMatricesView::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

void CMatricesView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_opengl.SetSize(cx, cy);
}

CMatricesDoc* CMatricesView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatricesDoc)));
	return (CMatricesDoc*)m_pDocument;
}
#endif //_DEBUG


// CMatricesView 消息处理程序

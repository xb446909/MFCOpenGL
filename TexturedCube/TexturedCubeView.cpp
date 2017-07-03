
// TexturedCubeView.cpp : CTexturedCubeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TexturedCube.h"
#endif

#include "TexturedCubeDoc.h"
#include "TexturedCubeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTexturedCubeView

IMPLEMENT_DYNCREATE(CTexturedCubeView, CView)

BEGIN_MESSAGE_MAP(CTexturedCubeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CTexturedCubeView 构造/析构

CTexturedCubeView::CTexturedCubeView()
{
	// TODO: 在此处添加构造代码

}

CTexturedCubeView::~CTexturedCubeView()
{
}

BOOL CTexturedCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTexturedCubeView 绘制

void CTexturedCubeView::OnDraw(CDC* /*pDC*/)
{
	CTexturedCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	m_opengl.RenderScene();
}


// CTexturedCubeView 打印

BOOL CTexturedCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTexturedCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTexturedCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTexturedCubeView 诊断

#ifdef _DEBUG
void CTexturedCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CTexturedCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTexturedCubeDoc* CTexturedCubeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTexturedCubeDoc)));
	return (CTexturedCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CTexturedCubeView 消息处理程序

int CTexturedCubeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CTexturedCubeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	if (m_pDC != NULL)
		delete m_pDC;
	m_pDC = NULL;
}

BOOL CTexturedCubeView::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

void CTexturedCubeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_opengl.SetSize(cx, cy);
}


// TrigleView.cpp : CTrigleView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Trigle.h"
#endif

#include "TrigleDoc.h"
#include "TrigleView.h"
#include "../common/shader.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "../GL/lib/glew32.lib")


// CTrigleView

IMPLEMENT_DYNCREATE(CTrigleView, CView)

BEGIN_MESSAGE_MAP(CTrigleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CTrigleView 构造/析构

CTrigleView::CTrigleView()
{
	// TODO: 在此处添加构造代码

}

CTrigleView::~CTrigleView()
{
}

BOOL CTrigleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTrigleView 绘制

void CTrigleView::OnDraw(CDC* /*pDC*/)
{
	CTrigleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	RenderScene();

}


// CTrigleView 打印

BOOL CTrigleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTrigleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTrigleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

BOOL CTrigleView::SetupPixelFormat(HDC hDC)
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
		1,                     // version number 
		PFD_DRAW_TO_WINDOW |   // support window 
		PFD_SUPPORT_OPENGL |   // support OpenGL 
		PFD_DOUBLEBUFFER,      // double buffered 
		PFD_TYPE_RGBA,         // RGBA type 
		24,                    // 24-bit color depth 
		0, 0, 0, 0, 0, 0,      // color bits ignored 
		0,                     // no alpha buffer 
		0,                     // shift bit ignored 
		0,                     // no accumulation buffer 
		0, 0, 0, 0,            // accum bits ignored 
		32,                    // 32-bit z-buffer 
		0,                     // no stencil buffer 
		0,                     // no auxiliary buffer 
		PFD_MAIN_PLANE,        // main layer 
		0,                     // reserved 
		0, 0, 0                // layer masks ignored 
	};
	int  iPixelFormat;

	// get the best available match of pixel format for the device context  
	if ((iPixelFormat = ChoosePixelFormat(hDC, &pfd)) == 0) return FALSE;
	if (!SetPixelFormat(hDC, iPixelFormat, &pfd)) return FALSE;
	return TRUE;
}

BOOL CTrigleView::InitOpenGL(HDC hDC)
{
	ASSERT(m_pDC != NULL);

	if (!SetupPixelFormat(hDC)) return FALSE;

	PIXELFORMATDESCRIPTOR pfd;

	int iPixelFormat = GetPixelFormat(hDC);

	DescribePixelFormat(hDC, iPixelFormat,
		sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	HGLRC  hglrc = wglCreateContext(hDC);
	if (!hglrc) return FALSE;
	if (!wglMakeCurrent(hDC, hglrc)) return FALSE;

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		MessageBox(_T("Failed to initialize GLEW"));
		return FALSE;
	}

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &m_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return TRUE;
}

void CTrigleView::RenderScene()
{
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//清除颜色缓冲区和深度缓冲区  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(m_programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);

	SwapBuffers(wglGetCurrentDC());
}


// CTrigleView 诊断

#ifdef _DEBUG
void CTrigleView::AssertValid() const
{
	CView::AssertValid();
}

void CTrigleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrigleDoc* CTrigleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrigleDoc)));
	return (CTrigleDoc*)m_pDocument;
}
#endif //_DEBUG


// CTrigleView 消息处理程序


int CTrigleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);

	if (!InitOpenGL(m_pDC->GetSafeHdc()))
		MessageBox(_T("Init opengl error"));

	return 0;
}


void CTrigleView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	glDeleteBuffers(1, &m_vertexbuffer);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

	HGLRC hrc = wglGetCurrentContext();
	if (wglMakeCurrent(0, 0) == FALSE)
	{
		MessageBox(_T("Could not make RC non-current"));
	}

	if (hrc)
	{
		if (::wglDeleteContext(hrc) == FALSE)
		{
			MessageBox(_T("Could not delete RC"));
		}
	}

	if (m_pDC != NULL)
		delete m_pDC;
	m_pDC = NULL;
}


BOOL CTrigleView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
}


void CTrigleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_nWidth = cx;
	m_nHeight = cy;
	if (m_nHeight == 0)
	{
		m_nHeight = 1;
	}
	glViewport(0, 0, m_nWidth, m_nHeight);
}

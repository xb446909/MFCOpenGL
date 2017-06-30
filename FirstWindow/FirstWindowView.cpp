
// FirstWindowView.cpp : CFirstWindowView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FirstWindow.h"
#endif

#include "FirstWindowDoc.h"
#include "FirstWindowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "../GL/lib/glew32.lib")

// CFirstWindowView

IMPLEMENT_DYNCREATE(CFirstWindowView, CView)

BEGIN_MESSAGE_MAP(CFirstWindowView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CFirstWindowView ����/����

CFirstWindowView::CFirstWindowView()
{
	// TODO: �ڴ˴���ӹ������

}

CFirstWindowView::~CFirstWindowView()
{
}

BOOL CFirstWindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFirstWindowView ����

void CFirstWindowView::OnDraw(CDC* /*pDC*/)
{
	CFirstWindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	RenderScene();
}


// CFirstWindowView ��ӡ

BOOL CFirstWindowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFirstWindowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFirstWindowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CFirstWindowView ���

#ifdef _DEBUG
void CFirstWindowView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstWindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstWindowDoc* CFirstWindowView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstWindowDoc)));
	return (CFirstWindowDoc*)m_pDocument;
}
#endif //_DEBUG


// CFirstWindowView ��Ϣ�������


BOOL CFirstWindowView::SetupPixelFormat(HDC hDC)
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

BOOL CFirstWindowView::InitOpenGL(HDC hDC)
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

	return TRUE;
}

void CFirstWindowView::RenderScene()
{
	//����������ɫΪ��ɫ  
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//�����ɫ����������Ȼ�����  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//͸��ͶӰ�任  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (double)m_nWidth / (double)m_nHeight, 1, 100);
	//�ӽǱ任  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	//�����ջ��������glPopMatrix()���Ӧ  
	glPushMatrix();

	glBegin(GL_LINES);
	glColor3d(1.0, 0.0, 0.0);   // X�� ��ɫ  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(2.0, 0.0, 0.0);
	glColor3d(0.0, 1.0, 0.0);   // Y�� ��ɫ  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 2.0, 0.0);
	glColor3d(0.0, 0.0, 1.0);   // Z�� ��ɫ  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 2.0);
	glEnd();

	glPopMatrix();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
}

int CFirstWindowView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pDC = new CClientDC(this);

	if (!InitOpenGL(m_pDC->GetSafeHdc()))
		MessageBox(_T("Init opengl error"));

	return 0;
}


void CFirstWindowView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

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


void CFirstWindowView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_nWidth = cx;
	m_nHeight = cy;
	if (m_nHeight == 0)
	{
		m_nHeight = 1;
	}
	glViewport(0, 0, m_nWidth, m_nHeight);
}


BOOL CFirstWindowView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


// TexturedCubeView.cpp : CTexturedCubeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CTexturedCubeView ����/����

CTexturedCubeView::CTexturedCubeView()
{
	// TODO: �ڴ˴���ӹ������

}

CTexturedCubeView::~CTexturedCubeView()
{
}

BOOL CTexturedCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTexturedCubeView ����

void CTexturedCubeView::OnDraw(CDC* /*pDC*/)
{
	CTexturedCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	m_opengl.RenderScene();
}


// CTexturedCubeView ��ӡ

BOOL CTexturedCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTexturedCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTexturedCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CTexturedCubeView ���

#ifdef _DEBUG
void CTexturedCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CTexturedCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTexturedCubeDoc* CTexturedCubeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTexturedCubeDoc)));
	return (CTexturedCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CTexturedCubeView ��Ϣ�������

int CTexturedCubeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pDC = new CClientDC(this);
	m_opengl.SetHDC(m_pDC->GetSafeHdc());
	if (!m_opengl.init())
		MessageBox(_T("Init opengl error"));

	return 0;
}

void CTexturedCubeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

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

	// TODO: �ڴ˴������Ϣ����������
	m_opengl.SetSize(cx, cy);
}

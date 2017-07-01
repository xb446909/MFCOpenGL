
// MatricesView.cpp : CMatricesView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMatricesView ����/����

CMatricesView::CMatricesView()
{
	// TODO: �ڴ˴���ӹ������

}


CMatricesView::~CMatricesView()
{
}

BOOL CMatricesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMatricesView ����

void CMatricesView::OnDraw(CDC* /*pDC*/)
{
	CMatricesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	m_opengl.RenderScene();
}


// CMatricesView ��ӡ

BOOL CMatricesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMatricesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMatricesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMatricesView ���

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

	// TODO:  �ڴ������ר�õĴ�������
	m_pDC = new CClientDC(this);
	m_opengl.SetHDC(m_pDC->GetSafeHdc());
	if (!m_opengl.init())
		MessageBox(_T("Init opengl error"));

	return 0;
}

void CMatricesView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

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

	// TODO: �ڴ˴������Ϣ����������
	m_opengl.SetSize(cx, cy);
}

CMatricesDoc* CMatricesView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatricesDoc)));
	return (CMatricesDoc*)m_pDocument;
}
#endif //_DEBUG


// CMatricesView ��Ϣ�������

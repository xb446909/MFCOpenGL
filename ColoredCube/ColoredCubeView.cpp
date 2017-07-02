
// ColoredCubeView.cpp : CColoredCubeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CColoredCubeView ����/����

CColoredCubeView::CColoredCubeView()
{
	// TODO: �ڴ˴���ӹ������

}

CColoredCubeView::~CColoredCubeView()
{
}

BOOL CColoredCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CColoredCubeView ����

void CColoredCubeView::OnDraw(CDC* /*pDC*/)
{
	CColoredCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CColoredCubeView ��ӡ

BOOL CColoredCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CColoredCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CColoredCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CColoredCubeView ���

#ifdef _DEBUG
void CColoredCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CColoredCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColoredCubeDoc* CColoredCubeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColoredCubeDoc)));
	return (CColoredCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CColoredCubeView ��Ϣ�������

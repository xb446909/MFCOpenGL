
// KeyboardMouseView.cpp : CKeyboardMouseView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CKeyboardMouseView ����/����

CKeyboardMouseView::CKeyboardMouseView()
{
	// TODO: �ڴ˴���ӹ������

}

CKeyboardMouseView::~CKeyboardMouseView()
{
}

BOOL CKeyboardMouseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CKeyboardMouseView ����

void CKeyboardMouseView::OnDraw(CDC* /*pDC*/)
{
	CKeyboardMouseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	RenderScene();
}


// CKeyboardMouseView ��ӡ

BOOL CKeyboardMouseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CKeyboardMouseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CKeyboardMouseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CKeyboardMouseView ���

#ifdef _DEBUG
void CKeyboardMouseView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyboardMouseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyboardMouseDoc* CKeyboardMouseView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyboardMouseDoc)));
	return (CKeyboardMouseDoc*)m_pDocument;
}
#endif //_DEBUG


// CKeyboardMouseView ��Ϣ�������

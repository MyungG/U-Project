
// DigitalFilterView.cpp : CDigitalFilterView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "DigitalFilter.h"
#endif

#include "DigitalFilterDoc.h"
#include "DigitalFilterView.h"
#include "Adj_Max.h"
#include "Convolution.h"
#include "DRAW_XY.h"
#include "DispSignal.h""

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDigitalFilterView

IMPLEMENT_DYNCREATE(CDigitalFilterView, CView)

BEGIN_MESSAGE_MAP(CDigitalFilterView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Xn, &CDigitalFilterView::OnXn)
	ON_COMMAND(ID_Hn, &CDigitalFilterView::OnHn)
	ON_COMMAND(ID_WhiteData, &CDigitalFilterView::OnWhitedata)
	ON_COMMAND(ID_DIGITALFILTEROUT, &CDigitalFilterView::OnDigitalfilterout)
	ON_COMMAND(ID_DIGITALFILTERFREQUENCY, &CDigitalFilterView::OnDigitalfilterfrequency)
END_MESSAGE_MAP()

// CDigitalFilterView ����/�Ҹ�

CDigitalFilterView::CDigitalFilterView()
{
	// �׻� �����ڿ��� �迭 �ʱ�ȭ
	for (int i = 0; i < 1024; i++)
	{
		m_InSignal[i] = 0;
		m_HnSignal[i] = 0;
		m_OutFilter[i] = 0;
		m_Display1[i] = 0;
		m_Display2[i] = 0;
		m_Display3[i] = 0;
		m_WhiteData[i] = 0;
	}

}

CDigitalFilterView::~CDigitalFilterView()
{
}

BOOL CDigitalFilterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CDigitalFilterView �׸���

void CDigitalFilterView::OnDraw(CDC* pDC)
{
	CDigitalFilterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	Draw_XY DX;
	DX.Disp_Coor(pDC);

	DispSignal DS;
	DS.DispDataNo = 1024;
	CPoint CP;

	for (int n = 0; n < 1024; n++)
	{
		DS.m_DispData[n] = m_Display1[n];
	}
	CP.x = 20;
	CP.y = 220;
	DS.DisplaySignal(pDC, CP, 100, 1);

	for (int n = 0; n < 1024; n++)
	{
		DS.m_DispData[n] = m_Display2[n];
	}
	CP.x = 20;
	CP.y = 420;
	DS.DisplaySignal(pDC, CP, 100, 1);
	for (int n = 0; n < 1024; n++)
	{
		DS.m_DispData[n] = m_Display3[n];
	}
	CP.x = 20;
	CP.y = 620;
	DS.DisplaySignal(pDC, CP, 100, 1);
}


// CDigitalFilterView �μ�

BOOL CDigitalFilterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CDigitalFilterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CDigitalFilterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CDigitalFilterView ����

#ifdef _DEBUG
void CDigitalFilterView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalFilterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalFilterDoc* CDigitalFilterView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalFilterDoc)));
	return (CDigitalFilterDoc*)m_pDocument;
}
#endif //_DEBUG


// CDigitalFilterView �޽��� ó����

#include "math.h"
void CDigitalFilterView::OnXn()
{
	// x(n)�� ����
	for (int n = 0; n < 1024; n++)
	{
		m_InSignal[n] = sin(2 * 3.14 * 1 * n / 1024) + sin(2 * 3.14 * 100 * n / 1024);
	}

	//x(n)�� ����ȭ
	Adj_Max AM;
	AM.m_Data_No = 1024;
	for (int n = 0; n < 1024; n++)
	{
		AM.AdMax[n] = m_InSignal[n];
	}
	AM.Sort_Max();
	for (int n = 0; n < 1024; n++)
	{
		m_Display1[n] = AM.AdMax[n];
	}
	Invalidate();
}


void CDigitalFilterView::OnHn()
{
	int m_Fc = 20;
	int m_FilterOrder = 1024;

	//h(n)�� ����
	for (int n = 1; n < m_FilterOrder; n++)
	{
		m_HnSignal[n] = fabs(sin(2 * 3.14*m_Fc*n) / double(3.14*n));
	}

	//h(n)�� ����ȭ
	Adj_Max AM;
	AM.m_Data_No = 1024;
	for (int n = 0; n < 1024; n++)
	{
		AM.AdMax[n] = m_HnSignal[n];
	}
	AM.Sort_Max();
	for (int n = 0; n < 1024; n++)
	{
		m_Display2[n] = AM.AdMax[n];
	}
	Invalidate();
}

// �������
void CDigitalFilterView::OnWhitedata()
{
	int RandNo;
	for (int n = 0; n < 1024; n++)
	{
		RandNo = rand() % 100 - 50;
		m_WhiteData[n] = double(RandNo) / 50;
	}

	for (int n = 0; n < 1024; n++)
	{
		m_Display1[n] = m_WhiteData[n];
	}
	Invalidate();
}

// x[n]�� h[n] Convolution
void CDigitalFilterView::OnDigitalfilterout()
{
	Convolution CV;
	CV.m_Co_Data1 = CV.m_Co_Data2 = 1024;
	for (int n = 0; n < 1024; n++)
	{
		CV.m_InData1[n] = m_InSignal[n];
		CV.m_InData2[n] = m_HnSignal[n];
	}
	CV.ConVol();
	for (int n = 0; n < 1024; n++)
	{
		m_OutFilter[n] = CV.m_OutData[n];
	}

	//����ȭ
	Adj_Max AM;
	AM.m_Data_No = 1024;
	for (int n = 0; n < 1024; n++)
	{
		AM.AdMax[n] = m_OutFilter[n];
	}
	AM.Sort_Max();
	for (int n = 0; n < 1024; n++)
	{
		m_Display3[n] = AM.AdMax[n];
	}

	Invalidate();
}

// ���ļ��������� ��ȯ
#include "Fourier.h"
void CDigitalFilterView::OnDigitalfilterfrequency()
{
	Fourier FT;
	FT.m_Data = 1024;

	//x[n]�� FT��ȯ�� ����ȭ�Ѵ��� Display[1]�� ����
	for (int n = 0; n < 1024; n++)
	{
		FT.m_FInData[n] = m_InSignal[n];
	}
	FT.Fourier_Fun();
	Adj_Max AM;
	AM.m_Data_No = 1024;
	for (int n = 0; n < 1024; n++)
	{
		AM.AdMax[n] = FT.m_OutData[n];
	}
	AM.Sort_Max();
	for (int n = 0; n < 1024; n++)
	{
		m_Display1[n] = AM.AdMax[n];
	}

	//h[n]�� FT��ȯ�� ����ȭ�Ѵ��� Display[2]�� ����
	for (int n = 0; n < 1024; n++)
	{
		FT.m_FInData[n] = m_HnSignal[n];
	}
	FT.Fourier_Fun();
	for (int n = 0; n < 1024; n++)
	{
		AM.AdMax[n] = FT.m_OutData[n];
	}
	AM.Sort_Max();
	for (int n = 0; n < 1024; n++)
	{
		m_Display2[n] = AM.AdMax[n];
	}

	//y[n]���� FT��ȯ�� ����ȭ�Ѵ��� Display[3]�� ����
	for (int n = 0; n < 1024; n++)
	{
		FT.m_FInData[n] = m_OutFilter[n];
	}
	FT.Fourier_Fun();
	for (int n = 0; n < 1024; n++)
	{
		AM.AdMax[n] = FT.m_OutData[n];
	}
	AM.Sort_Max();
	for (int n = 0; n < 1024; n++)
	{
		m_Display3[n] = AM.AdMax[n];
	}

	Invalidate();
}


// DigitalFilterView.cpp : CDigitalFilterView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Xn, &CDigitalFilterView::OnXn)
	ON_COMMAND(ID_Hn, &CDigitalFilterView::OnHn)
	ON_COMMAND(ID_WhiteData, &CDigitalFilterView::OnWhitedata)
	ON_COMMAND(ID_DIGITALFILTEROUT, &CDigitalFilterView::OnDigitalfilterout)
	ON_COMMAND(ID_DIGITALFILTERFREQUENCY, &CDigitalFilterView::OnDigitalfilterfrequency)
END_MESSAGE_MAP()

// CDigitalFilterView 생성/소멸

CDigitalFilterView::CDigitalFilterView()
{
	// 항상 생성자에서 배열 초기화
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDigitalFilterView 그리기

void CDigitalFilterView::OnDraw(CDC* pDC)
{
	CDigitalFilterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

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


// CDigitalFilterView 인쇄

BOOL CDigitalFilterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDigitalFilterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDigitalFilterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDigitalFilterView 진단

#ifdef _DEBUG
void CDigitalFilterView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalFilterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalFilterDoc* CDigitalFilterView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalFilterDoc)));
	return (CDigitalFilterDoc*)m_pDocument;
}
#endif //_DEBUG


// CDigitalFilterView 메시지 처리기

#include "math.h"
void CDigitalFilterView::OnXn()
{
	// x(n)값 설정
	for (int n = 0; n < 1024; n++)
	{
		m_InSignal[n] = sin(2 * 3.14 * 1 * n / 1024) + sin(2 * 3.14 * 100 * n / 1024);
	}

	//x(n)값 정규화
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

	//h(n)값 설정
	for (int n = 1; n < m_FilterOrder; n++)
	{
		m_HnSignal[n] = fabs(sin(2 * 3.14*m_Fc*n) / double(3.14*n));
	}

	//h(n)값 정규화
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

// 백색잡음
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

// x[n]과 h[n] Convolution
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

	//정규화
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

// 주파수영역으로 변환
#include "Fourier.h"
void CDigitalFilterView::OnDigitalfilterfrequency()
{
	Fourier FT;
	FT.m_Data = 1024;

	//x[n]을 FT변환후 정규화한다음 Display[1]에 저장
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

	//h[n]을 FT변환후 정규화한다음 Display[2]에 저장
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

	//y[n]값을 FT변환후 정규화한다음 Display[3]에 저장
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

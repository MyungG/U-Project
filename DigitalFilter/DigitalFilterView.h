
// DigitalFilterView.h : CDigitalFilterView 클래스의 인터페이스
//

#pragma once


class CDigitalFilterView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDigitalFilterView();
	DECLARE_DYNCREATE(CDigitalFilterView)

// 특성입니다.
public:
	CDigitalFilterDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDigitalFilterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnXn();
	afx_msg void OnHn();
	afx_msg void OnWhitedata();
	afx_msg void OnDigitalfilterout();
	afx_msg void OnDigitalfilterfrequency();
public:
	double m_InSignal[1024]; 
	double m_HnSignal[1024];
	double m_OutFilter[1024];
	double m_Display1[1024];
	double m_Display2[1024];
	double m_Display3[1024];
	double m_WhiteData[1024];

};

#ifndef _DEBUG  // DigitalFilterView.cpp의 디버그 버전
inline CDigitalFilterDoc* CDigitalFilterView::GetDocument() const
   { return reinterpret_cast<CDigitalFilterDoc*>(m_pDocument); }
#endif


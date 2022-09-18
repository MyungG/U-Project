
// DigitalFilterView.h : CDigitalFilterView Ŭ������ �������̽�
//

#pragma once


class CDigitalFilterView : public CView
{
protected: // serialization������ ��������ϴ�.
	CDigitalFilterView();
	DECLARE_DYNCREATE(CDigitalFilterView)

// Ư���Դϴ�.
public:
	CDigitalFilterDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CDigitalFilterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // DigitalFilterView.cpp�� ����� ����
inline CDigitalFilterDoc* CDigitalFilterView::GetDocument() const
   { return reinterpret_cast<CDigitalFilterDoc*>(m_pDocument); }
#endif


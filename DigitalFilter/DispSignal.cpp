#include "stdafx.h"
#include "DispSignal.h"


DispSignal::DispSignal()
{
	for (int Time = 0; Time < DispDataNo; Time++)
		m_DispData[Time] = 0;
}


DispSignal::~DispSignal()
{
}

void DispSignal::DisplaySignal(CDC*pDC, CPoint CP, int Mag, BOOL Line_Dot)
{
	if (Line_Dot)
	{
		CPen pen(PS_SOLID, 1, RGB(5, 5, 255));
		CPen *pOldPen = pDC->SelectObject(&pen);
		for (int Time = 0; Time < DispDataNo; Time++)
		{
			pDC->MoveTo(CP.x + Time, CP.y);
			pDC->LineTo(CP.x + Time, CP.y - m_DispData[Time] * Mag); // Mag(ΑυΖψµµ)
		}
		pDC->SelectObject(pOldPen);
	}
	else
	{
		COLORREF color = RGB(255, 0, 0);
		for (int Time = 0; Time < DispDataNo; Time++)
		{
			pDC->SetPixel(CP.x + Time, CP.y - m_DispData[Time] * Mag, color);
		}
	}
}
void DispSignal::DisplaySignalDot(CDC*pDC, CPoint CP, int Mag)
{
	COLORREF color = RGB(255, 0, 0);
	for (int Time = 0; Time < DispDataNo; Time++)
		pDC->SetPixel(CP.x + Time, CP.y - m_DispData[Time] * Mag, color);
}
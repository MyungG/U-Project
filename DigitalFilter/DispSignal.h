#pragma once
#define Sort 6;
class DispSignal
{
public:
	DispSignal();
	~DispSignal();
	int DispDataNo;
	double m_DispData[2048];
	void DisplaySignal(CDC*pDC, CPoint CP, int Mag, BOOL Line_Dot);
	void DisplaySignalDot(CDC*pDC, CPoint CP, int Mag);
};


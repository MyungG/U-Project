#pragma once
class Fourier
{
public:
	int m_Data;
	double *m_FInData, *m_OutData;
public:
	Fourier();
	~Fourier();
	
	void Fourier_Fun();
};


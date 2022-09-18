#include "stdafx.h"
#include "Fourier.h"


#include <math.h>
#define Total_No 1024
#define Pi 3.14
Fourier::Fourier()
{
	m_FInData = new double[Total_No];
	m_OutData = new double[Total_No];
	for(int i = 0; i < Total_No; i++)
	{
		m_FInData[i] = m_OutData[i] = 0;
	}
	
}


Fourier::~Fourier()
{
	delete[]m_FInData;
	delete[]m_OutData;
}

void Fourier::Fourier_Fun()
{
	double m_Real, m_Image;
	double T_Real, T_Image;
	for (int fre = 0; fre < m_Data; fre++)
	{
		T_Real = T_Image = 0;
		for (int n = 0; n < m_Data; n++)
		{
			m_Real = m_FInData[n] * cos(2 * Pi*fre*n / m_Data);
			m_Image = m_FInData[n] * sin(2 * Pi*fre*n / m_Data);
			T_Real += m_Real;
			T_Image += m_Image;
		}
		m_OutData[fre] = sqrt(T_Real*T_Real + T_Image*T_Image) / 1024;
	}
}

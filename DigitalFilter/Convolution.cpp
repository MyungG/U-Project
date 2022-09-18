#include "stdafx.h"
#include "Convolution.h"


Convolution::Convolution()
{
	// ��ǲ, �ƿ�ǲ �迭 �ʱ�ȭ
	for (int i = 0; i < Total_No; i++)
	{
		m_InData1[i] = m_InData2[i] = 0;
	}
	for (int i = 0; i < Total_No * 2; i++)
	{
		m_OutData[i] = 0;
	}
}


Convolution::~Convolution()
{
}

void Convolution :: ConVol()
{
	for (int n = 0; n < (m_Co_Data1 + m_Co_Data2); n++) // Convolution�� Ư������Ͽ� ������ ���� ����
	{
		m_OutData[n] = 0;
		for (int k = 0; k <= n; k++)
		{
			m_OutData[n] += m_InData1[k] * m_InData2[n - k]; // Convolution
		}
	}
}



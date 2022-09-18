#pragma once
#define Total_No 1024
class Convolution
{
public:
	int m_Co_Data1, m_Co_Data2;
	double m_InData1[Total_No];
	double m_InData2[Total_No];
	double m_OutData[Total_No * 2];
public:
	Convolution();
	~Convolution();
public:
	void ConVol(void);
};


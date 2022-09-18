#include "stdafx.h"
#include "Draw_XY.h"


Draw_XY::Draw_XY()
{
}


Draw_XY::~Draw_XY()
{
}

// 화면상에 좌표축 그리기
void Draw_XY::Disp_Coor(CDC*pDC)
{
	pDC->Rectangle(X_Start, Y_Start, X_End, Y_End);


	pDC->MoveTo(X_Start, Y_Start + 200);
	pDC->LineTo(X_End, Y_Start + 200);

	pDC->MoveTo(X_Start, Y_Start + 400);
	pDC->LineTo(X_End, Y_Start + 400);

	pDC->MoveTo(X_Start, Y_Start + 600);
	pDC->LineTo(X_End, Y_Start + 600);

	pDC->Rectangle(X_End, Y_Start, X_End + 1024, Y_End);

	pDC->MoveTo(X_End, Y_Start + 200);
	pDC->LineTo(X_End + 1024, Y_Start + 200);

	pDC->MoveTo(X_End, Y_Start + 400);
	pDC->LineTo(X_End + 1024, Y_Start + 400);

	pDC->MoveTo(X_End, Y_Start + 600);
	pDC->LineTo(X_End + 1024, Y_Start + 600);
}
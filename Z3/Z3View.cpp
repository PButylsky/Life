
// Z3View.cpp : implementation of the CZ3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Z3.h"
#endif

#include "Z3Doc.h"
#include "Z3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CZ3View

IMPLEMENT_DYNCREATE(CZ3View, CView)

BEGIN_MESSAGE_MAP(CZ3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

int delta = 0;

int X_NUM = 0, Y_NUM = 0;
int X_DOT = 0, Y_DOT = 0;

// CZ3View construction/destruction

CZ3View::CZ3View()
{
	// TODO: add construction code here
	Clean();

}

CZ3View::~CZ3View()
{

}

BOOL CZ3View::PreCreateWindow(CREATESTRUCT& cs)


{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CZ3View drawing

void CZ3View::OnDraw(CDC* pDC)
{
	CZ3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	return;

	int i, j;

	CBrush aBrush(BS_SOLID, RGB(0, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&aBrush);	//Выбрать кисть в контекст устройства
	pOldBrush = (CBrush*)pDC->SelectStockObject(BLACK_BRUSH);

	for (j = 0; j < ARSY; j++)
	{
		for (i = 0; i < ARSX; i++)
		{
			if (ARR[0][j][i] == 1)
			{
				X_NUM = i*STEP;
				Y_NUM = j*STEP;
				CRect aRect((X_NUM - RAD), (Y_NUM - RAD), (X_NUM + RAD), (Y_NUM + RAD));
				pDC->Ellipse(aRect);
			}
		}
	}
}


// CZ3View printing

BOOL CZ3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CZ3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CZ3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CZ3View diagnostics

#ifdef _DEBUG
void CZ3View::AssertValid() const
{
	CView::AssertValid();
}

void CZ3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZ3Doc* CZ3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZ3Doc)));
	return (CZ3Doc*)m_pDocument;
}
#endif //_DEBUG



// CZ3View message handlers


void CZ3View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnChar(nChar, nRepCnt, nFlags);


	int value = nChar;
	InvalidateRect(nullptr);

	switch (value) {
	case (32):	// Space - next step
		value = 0;
		CalcFig();
		InvalidateRect(nullptr);
		break;

	case(99):	//c - clear
		Clean();
		value = 0;
		break;

	case(101):	//e - Exit
	
		value = 0;
		break;

	case(105):	// i - input
		Clean();
		SetFig();
		InvalidateRect(nullptr);
		value = 0;
		break;

	case(111):	//o - save to file life.dat
		value = 0;
//		ReadFig();
		break;

	case(114):	//r - read file life.dat
		Clean();
		ReadFig();
		InvalidateRect(nullptr);
		value = 0;
		break;

	case(115):	// s - save resukt
		value = 0;
		SaveFig();
//		InvalidateRect(nullptr);
		break;
	}
}

void CZ3View::Clean()
{
	int i=0;
	int j=0;

	for(int j = 0; j < ARSY; j++)
	{
		for(int i = 0; i < ARSX; i++)
		{
			ARR[0][j][i] = 0;
		}
	}
}

void CZ3View::SetFig()
{
//	крест
	ARR [0] [10] [30] = 1;
	ARR [0] [9] [30] = 1;
	ARR [0] [11] [30] = 1;
	ARR [0] [10] [29] = 1;
	ARR [0] [10] [31] = 1;

//	ромб	
	ARR [0] [10] [10] = 1;
	ARR [0] [10] [11] = 1;
	ARR [0] [11] [9] = 1;
	ARR [0] [11] [10] = 1;
	ARR [0] [10] [12] = 1;
	ARR [0] [11] [11] = 1;

// зюзюка
	ARR[0][30][30] = 1;
	ARR[0][30][29] = 1;
	ARR[0][30][28] = 1;
	ARR[0][30][31] = 1;
	ARR[0][30][32] = 1;
	ARR[0][30][33] = 1;
	ARR[0][30][27] = 1;
	ARR[0][29][30] = 1;
	ARR[0][31][30] = 1;
	ARR[0][29][27] = 1;
	ARR[0][31][27] = 1;
	ARR[0][29][33] = 1;
	ARR[0][31][33] = 1;
}

void CZ3View::CalcFig()
{
	int i, j, SIGN = 0;

	for (j = 1; j < ARSY-1; j++)
	{
		for (i = 1; i < ARSX-1; i++)
		{
			if (ARR[0][j - 1][i - 1] == 1) SIGN++;
			if (ARR[0][j][i - 1] == 1) SIGN++;
			if (ARR[0][j + 1][i - 1] == 1) SIGN++;
			if (ARR[0][j - 1][i] == 1) SIGN++;
			if (ARR[0][j + 1][i] == 1) SIGN++;
			if (ARR[0][j][i + 1] == 1) SIGN++;
			if (ARR[0][j - 1][i + 1] == 1) SIGN++;
			if (ARR[0][j + 1][i + 1] == 1) SIGN++;

			if (SIGN < 2) ARR[1][j][i] = 0;
			if (SIGN == 2) ARR[1][j][i] = ARR[0][j][i];
			if (SIGN > 3) ARR[1][j][i] = 0;
			if (SIGN == 3) ARR[1][j][i] = 1;

			SIGN = 0;
		}
	}
 	for (j = 0; j < ARSY; j++)
	{
		for (i = 0; i < ARSX; i++)
		{
			ARR[0][j][i] = ARR[1][j][i];
		}
	}	
}

void CZ3View::InputFig()
{
	if (delta == 0)
	{
		return;
	}
}

//void CZ3View::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CView::OnLButtonDblClk(nFlags, point);
//}


void CZ3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);

	X_DOT = point.x;
	Y_DOT = point.y;

	delta = X_DOT % STEP;
	if (delta < 3)
		X_NUM = X_DOT / STEP;
	else
		X_NUM = X_DOT / STEP + 1;
	delta = Y_DOT % STEP;
	if (delta < 3)
	{
		Y_NUM = Y_DOT / STEP;
	}
	else
	{
		Y_NUM = Y_DOT / STEP + 1;
	}

	
	if((ARR[0][Y_NUM][X_NUM] != 0) && (ARR[0][Y_NUM][X_NUM] != 1)) ARR[0][Y_NUM][X_NUM] = 0;
	
	if (ARR[0][Y_NUM][X_NUM] == 0)
	{
		ARR[0][Y_NUM][X_NUM] = 1;
	}
	else
	{
		ARR[0][Y_NUM][X_NUM] = 0;
	}

	InvalidateRect(nullptr);
}

void CZ3View::SaveFig()
{
	int i, j;
	int LGAB=0, RGAB=0, TGAB=0, BGAB=0, SIZE_Y = 0, SIZE_X = 0;

	str = s1 = "";
	s2 = "\n";

	ni = 0; len = 0;

	for (i = 0; i < ARSX; i++)
	{
		for (j = 0; j < ARSY; j++)
		{
			if (ARR[0][j][i] == 1)
			{
				LGAB = i;
				i = ARSX; j = ARSY;
			}
		}
	}
	for (i = ARSX-1; i > 0; i--)
	{
		for (j = 0; j < ARSY; j++)
		{
			if (ARR[0][j][i] == 1)
			{
				RGAB = i;
				i = 0; j = ARSY;
			}
		}
	}
	for (j = 0; j < ARSY; j++)
	{
		for (i = 0; i < ARSX; i++)
		{
			if (ARR[0][j][i] == 1)
			{
				TGAB = j;
				i = ARSX; j = ARSY;
			}
		}
	}
	for (j = ARSY-1; j > 0; j--)
	{
		for (i = 0; i < ARSX; i++)
		{
			if (ARR[0][j][i] == 1)
			{
				BGAB = j;
				i = ARSX; j = 0;
			}
		}
	}
	SIZE_Y = BGAB - TGAB;
	SIZE_X = RGAB - LGAB;
	len = SIZE_X * SIZE_Y;

	stream = fopen("life.dat", "wb");

	fprintf(stream, "%d ", TGAB);
	fprintf(stream, "%d ", BGAB);
	fprintf(stream, "%d ", LGAB);
	fprintf(stream, "%d ", RGAB);

	for (j = TGAB; j <= BGAB; j++)
	{
		for (i = LGAB; i <= RGAB; i++)
		{
			fprintf(stream, "%d ", ARR[0][j][i]);
		}
	}

	fclose(stream);
}

void CZ3View::ReadFig()
{
	int i, j;
	int LGAB = 0, RGAB = 0, TGAB = 0, BGAB = 0, SIZE_Y = 0, SIZE_X = 0;

	stream = fopen("life.dat", "rb");

	fscanf(stream, "%d ", &TGAB);
	fscanf(stream, "%d ", &BGAB);
	fscanf(stream, "%d ", &LGAB);
	fscanf(stream, "%d ", &RGAB);

	for(j=TGAB; j <= BGAB; j++)
	{
		for(i=LGAB; i <= RGAB; i++)
		{
			fscanf(stream, "%d ", &ARR[0][j][i]);
		}
	}
	fclose(stream);
}

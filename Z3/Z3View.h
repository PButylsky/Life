
// Z3View.h : interface of the CZ3View class
//

#pragma once
#pragma warning(disable:4996)


class CZ3View : public CView
{
protected: // create from serialization only
	CZ3View();
	DECLARE_DYNCREATE(CZ3View)

// Attributes
public:
	CZ3Doc* GetDocument() const;

public:
#define ARSX 160
#define ARSY 85
#define STEP 10
#define RAD 4
#define SH 5

int ARR[2][ARSY][ARSX];

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC); // overridden to draw this view
//	virtual void OnDrawBorder(CDC* pDC);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CZ3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	CString str, s1, s2;
	int ni, len;
	FILE *stream;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void SetFig();
	afx_msg void CalcFig();
	afx_msg void InputFig();
	afx_msg void SaveFig();
	afx_msg void Clean();
	afx_msg void ReadFig();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Z3View.cpp
inline CZ3Doc* CZ3View::GetDocument() const
   { return reinterpret_cast<CZ3Doc*>(m_pDocument); }
#endif






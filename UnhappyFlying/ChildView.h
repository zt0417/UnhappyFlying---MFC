/*
*  FILE          : ChildView.cpp
*  PROJECT       : PROG2215 - Assignment #3
*  PROGRAMMER    : Tong Zhang
*  FIRST VERSION : 2016-04-03
*  DESCRIPTION   : The Unhappy Flying Reptiles software application is designed to teach you the fundamentals of
*				   bitmap manipulate and real time multimedia application development.
*
*				   We will be enhancing many of the deliverables you've already worked in A1 and A2. The UFR's
*				   will become more animated as they flap about the screen. There will be a stack of 6 boxes that
*				   you will need to animate in the vent of a collosion. There are several new facets here that continue
*				   to have you explore the realm of GAS. you application will of course have to perform well, so do expect
*				   part of the grade to be based on demostrating any improvements or sound techniques for ensuring excellent,
*				   well-performing application.
*/


// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

	// images properties.
	Bitmap* backImg;		// contains background image.
	Bitmap* midImg;			// contains middle image.
	Bitmap* foreImg;		// contains fore image.
	Bitmap* rotateReptile;  // contains rotate reptile image.
	Bitmap* reptile;		// contians reptile image.
	Bitmap* Boxes;			// contains box image.
	Bitmap* featherImage;   // contains feather image.

	// other properties
	int counter;			// counter
	int Number;				// score for shooting.
	std::string mark;		// final mark.
	
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	// functions.
	void LoadBirdImage(int counter);
	void LoadRotateBirdImage(int counter);
	void AutoLoadBoxeImage(void);
	int IsCrashObject(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int whichBox);
	float rateWidthWindows(int width);
	float rateHeightWindows(int height);
};


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

// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "UnhappyFlying.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView
CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	// window load image when create Window.
	backImg = (Bitmap *)Image::FromFile(L"./res/Background.bmp");
	midImg = (Bitmap *)Image::FromFile(L"./res/Midground.bmp");
	foreImg = (Bitmap *)Image::FromFile(L"./res/Foreground.bmp");
	reptile = (Bitmap *)Image::FromFile(L"./res/frame-1.png");
	Boxes = (Bitmap *)Image::FromFile(L"./res/Cup.png");
	featherImage = (Bitmap *)Image::FromFile(L"./res/xue.png");

	// set some counter and string.
	counter = 1;													// bounter for bird flying.
	Number = 0;														// final mark.
	mark = "000";													// final mark string.

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

bool initialTime = false;			// Set timer just for the first time.
int Xposition = 60;					// The X point for the bird.
int Yposition = 50;					// The Y point for the bird.

// rotate virieables.
float fill_Angle = 5.0;
float fill_Angle1 = 90.0;
bool isHit = false;					// the bird is shot.
bool isHitGround = false;			// the bird is hit on ground.
bool flying = true;					// the bird is flying.
bool xueShow = true;				// show blood on bird image when bird is hit by user.
bool start = true;					// the flag for game is start.

int length1 = 50;					// flying length of distance for number one object.
int length2 = 50;					// flying length of distance for number two object.
int length3 = 60;					// flying length of distance for number three object.
int length4 = 50;					// flying length of distance for number four object.
int length5 = 60;					// flying length of distance for number five object.
int length6 = 60;					// flying length of distance for number six object.

bool isCrash = false;				// the flag for two object is crashed.

bool goingUp = false;				// the bird is going up.
bool goingDown = false;				// the bird is going down.

bool goingRight = false;			// the bird is going right.
bool goingLeft = false;				// the bird is going left.
bool rotate = true;					// the bird is rotate
int flyingCounter = 0;				// the flying counter to change image when bird is flying.
int temp = 2;						// keep while time.

float widthRate = 0;				// when windows change size, and get rate of width to change some image.
float heightRate = 0;				// when windows change size, and get rate of height to change some image.


void CChildView::OnPaint() 
{
	int result = 1; // get random number.
	// generate random number.
	srand(time(NULL));
	result = rand() % 2 + 1;

	if (flyingCounter >= 30)
	{
		flyingCounter = 1;
	}


	// if flying is true.
	if (flying == true)
	{
		// animation about bird is flying.
		if (counter > 4)
		{
			// reset counter to one.
			counter = 1;
		}

		if (rotate == true)
		{
			// load difference bird iamge.
			if (result == 1)
			{
				goingLeft = true;
				goingRight = false;				
			}
			else if (result == 2)
			{
				goingRight = true;
				goingLeft = false;
			}

			temp = result;
			rotate = false;
		}
	}


	if (temp == 2)
	{
		LoadBirdImage(counter);
	}
	else if (temp == 1)
	{
		LoadRotateBirdImage(counter);
	}



	// change boxes iamge when game start again.
	if (start == false)
	{
		// calling AutoLoadBoxeImage() to change boxes images.
		AutoLoadBoxeImage();
		// reset start flag to true.
		start = true;
	}


	// set timer.
	if (initialTime == false)
	{
		SetTimer(1, 60, NULL);
		initialTime = true;
	}

	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	Gdiplus::Font font(&FontFamily(L"Arial"), 24);
	LinearGradientBrush brush(RectF(0, 0, 100, 100), Color::Red, Color::Yellow, LinearGradientModeHorizontal);

	//Get the size of sling.
	//int slingshotWidth = slingshot1->GetWidth();
	//int slingshotHeight = slingshot1->GetHeight();

	//Get the size of background.
	int backgroundWidth = backImg->GetWidth();
	int backgroundHeight = backImg->GetHeight();

	//Instance a ImageAttributes.
	ImageAttributes imgAttr;

	//Instance Crect.
	CRect Rect;
	GetClientRect(&Rect);  //Get the window rect.

	widthRate = rateWidthWindows(Rect.Width());
	heightRate = rateHeightWindows(Rect.Height());
	
	// Resize the windows , sling and repitile rect.
	RectF rectf(0, 0, Rect.Width(), Rect.Height());
	// RectF mySlingRect((rectf.GetLeft() + 60), (rectf.GetBottom() - 140), slingshotWidth * widthRate, slingshotHeight * heightRate);
	RectF myRepitileRect(Xposition * widthRate, Yposition * heightRate, 64 * widthRate, 64 * heightRate);
	RectF xueBox((myRepitileRect.X + 10) * widthRate, (myRepitileRect.Y + 10) * heightRate, 10 * widthRate, 10 * heightRate);

	// set 6 six boxes into RectF object.
	RectF boxe1((rectf.GetLeft() + 600) * widthRate, (rectf.GetBottom() - 50 * heightRate), 50 * widthRate, 50 * heightRate);
	RectF boxe2((rectf.GetLeft() + 650) * widthRate, (rectf.GetBottom() - 50 * heightRate), 50 * widthRate, 50 * heightRate);
	RectF boxe3((rectf.GetLeft() + 700) * widthRate, (rectf.GetBottom() - 50 * heightRate), 50 * widthRate, 50 * heightRate);
	RectF boxe4((rectf.GetLeft() + 625) * widthRate, (rectf.GetBottom() - 100 * heightRate), 50 * widthRate, 50 * heightRate);
	RectF boxe5((rectf.GetLeft() + 675) * widthRate, (rectf.GetBottom() - 100 * heightRate), 50 * widthRate, 50 * heightRate);
	RectF boxe6((rectf.GetLeft() + 650) * widthRate, (rectf.GetBottom() - 150 * heightRate), 50 * widthRate, 50 * heightRate);

	// set blood
	RectF featherImageR(0, 0, Rect.Width(), Rect.Height());

	//Get the size for the rectangle.
	int left = Rect.left;
	int top = Rect.top;
	int width = Rect.right - Rect.left;
	int height = Rect.bottom - Rect.top;

	//Create a device consistent with a particular scene memory device context.
	HDC hdcMem = ::CreateCompatibleDC(dc);
	const int nMemDC = ::SaveDC(hdcMem);


	//Create target dc compatibility with bitmaps by CreateCompatibleBitmap.
	HBITMAP hBitmap = ::CreateCompatibleBitmap(dc, width, height);

	//Compatible bitmap selected into the dc compatible.
	::SelectObject(hdcMem, hBitmap);


	//Get a handle to the GDI+ Graphics object linked to the window's device context.
	Graphics graphics(hdcMem);
	SolidBrush back(Color(255, 255, 255));
	graphics.FillRectangle(&back, left, top, width, height);

	//Set a range of pixel colors in the Bitmap to be transparent.
	imgAttr.SetColorKey(Color(0, 100, 0), Color(120, 255, 40));
	
	//reptile->RotateFlip(RotateNoneFlipX);
	//Draw to backbuffer bitmap here
	graphics.DrawImage(backImg, rectf, 0, 0, backgroundWidth, backgroundHeight, UnitPixel, &imgAttr);
	graphics.DrawImage(midImg, rectf, 0, 0, backgroundWidth, backgroundHeight, UnitPixel, &imgAttr);
	graphics.DrawImage(foreImg, rectf, 0, 0, backgroundWidth, backgroundHeight, UnitPixel, &imgAttr);

	// stream used for the conversion.
	std::ostringstream convert;   
	// insert the textual representation of 'Number' in the characters in the stream.
	convert << mark;
	// set 'Result' to the contents of the stream.
	mark = convert.str(); 

	// Convert string to const wchar_t*.
	std::wstring name(mark.begin(), mark.end());
	const wchar_t* szName = name.c_str();
	// show score for user.
	graphics.DrawString(szName, -1, &font, PointF(0, 0), &brush);



	// drawing new positon of bird.
	// If the bird is shot.
	if (isHit == true)
	{
		// 
		if (xueShow == true)
		{
			graphics.DrawImage(featherImage, featherImageR);
			xueShow = false;

			//add 100 to mark.
			Number += 100;
			mark = std::to_string(Number);
		}

		flying = false;
		// If the bird is hit on Ground.
		if (Yposition >= (Rect.bottom - 64))
		{
			// set isHitGround flag to true.
			isHitGround = true;
			// set isHit flag to false;
			isHit = false;			
		}
		else // If the bird is not hit on Ground.
		{
			// check the bird crash the first box. 
			if (1 == IsCrashObject(Xposition, Yposition, 60 * widthRate, 60 * heightRate, boxe1.X, boxe1.Y, 50 * widthRate, 50 * heightRate, 1))
			{
				isCrash = true;
			};

			// check the bird crash the second box. 
			if (2 == IsCrashObject(Xposition, Yposition, 60 * widthRate, 60 * heightRate, boxe2.X, boxe2.Y, 50 * widthRate, 50 * heightRate, 2))
			{
				isCrash = true;
			};

			// check the bird crash the three box. 
			if (3 == IsCrashObject(Xposition, Yposition, 60 * widthRate, 60 * heightRate, boxe3.X, boxe3.Y, 50 * widthRate, 50 * heightRate, 3))
			{
				isCrash = true;
			};

			// check the bird crash the four box. 
			if (4 == IsCrashObject(Xposition, Yposition, 60 * widthRate, 60 * heightRate, boxe4.X, boxe4.Y, 50 * widthRate, 50 * heightRate, 4))
			{
				isCrash = true;
			};

			// check the bird crash the five box. 
			if (5 == IsCrashObject(Xposition, Yposition, 60 * widthRate, 60 * heightRate, boxe5.X, boxe5.Y, 50 * widthRate, 50 * heightRate, 5))
			{
				isCrash = true;
			};

			// check the bird crash the six box. 
			if (6 == IsCrashObject(Xposition, Yposition, 60 * widthRate, 60 * heightRate, boxe6.X, boxe6.Y, 50 * widthRate, 50 * heightRate, 6))
			{
				isCrash = true;
			};

			// if the bird is crash the one of six boxes 
			if (isCrash == true)
			{
				// calling ResetTransform() to reset transform.
				graphics.ResetTransform();

				// calling RotateTransform to rotate pictrue of bird.
				graphics.RotateTransform(fill_Angle1, MatrixOrderAppend);
				// calling TranslateTransform to set new X, Y position to translate to new position.
				graphics.TranslateTransform(boxe1.X + length1, boxe1.Y, MatrixOrderAppend);
				graphics.DrawImage(Boxes, -boxe1.Width, -boxe1.Height / 2, boxe1.Width, boxe1.Height);

				fill_Angle1 += 23.0;
				length1 += 50;

				// calling ResetTransform() to reset transform.
				graphics.ResetTransform();

				// calling RotateTransform to rotate pictrue of bird.
				graphics.RotateTransform(fill_Angle1, MatrixOrderAppend);
				// calling TranslateTransform to set new X, Y position to translate to new position.
				graphics.TranslateTransform(boxe2.X + length2, boxe2.Y, MatrixOrderAppend);
				graphics.DrawImage(Boxes, -boxe2.Width, -boxe2.Height / 2, boxe2.Width, boxe2.Height);

				fill_Angle1 += 23.0;
				length2 += 50;

				// calling ResetTransform() to reset transform.
				graphics.ResetTransform();

				// calling RotateTransform to rotate pictrue of bird.
				graphics.RotateTransform(fill_Angle1, MatrixOrderAppend);
				// calling TranslateTransform to set new X, Y position to translate to new position.
				graphics.TranslateTransform(boxe3.X + length3, boxe3.Y, MatrixOrderAppend);
				graphics.DrawImage(Boxes, -boxe3.Width, -boxe3.Height / 2, boxe3.Width, boxe3.Height);

				fill_Angle1 += 23.0;
				length3 += 60;

				// calling ResetTransform() to reset transform.
				graphics.ResetTransform();

				// calling RotateTransform to rotate pictrue of bird.
				graphics.RotateTransform(fill_Angle1, MatrixOrderAppend);
				// calling TranslateTransform to set new X, Y position to translate to new position.
				graphics.TranslateTransform(boxe4.X + length4, boxe4.Y, MatrixOrderAppend);
				graphics.DrawImage(Boxes, -boxe4.Width, -boxe4.Height / 2, boxe4.Width, boxe4.Height);

				fill_Angle1 += 23.0;
				length4 += 50;

				// calling ResetTransform() to reset transform.
				graphics.ResetTransform();

				// calling RotateTransform to rotate pictrue of bird.
				graphics.RotateTransform(fill_Angle1, MatrixOrderAppend);
				// calling TranslateTransform to set new X, Y position to translate to new position.
				graphics.TranslateTransform(boxe5.X + length5, boxe5.Y, MatrixOrderAppend);
				graphics.DrawImage(Boxes, -boxe5.Width, -boxe5.Height / 2, boxe5.Width, boxe5.Height);


				fill_Angle1 += 23.0;
				length5 += 60;

				// calling ResetTransform() to reset transform.
				graphics.ResetTransform();

				// calling RotateTransform to rotate pictrue of bird.
				graphics.RotateTransform(fill_Angle1, MatrixOrderAppend);
				// calling TranslateTransform to set new X, Y position to translate to new position.
				graphics.TranslateTransform(boxe6.X + length1, boxe6.Y, MatrixOrderAppend);
				graphics.DrawImage(Boxes, -boxe6.Width, -boxe6.Height / 2, boxe6.Width, boxe6.Height);

				fill_Angle1 += 23.0;
				length6 += 60;

			}
			else // otherwise.
			{
				// draw all boxe images.
				graphics.DrawImage(Boxes, boxe1);
				graphics.DrawImage(Boxes, boxe2);
				graphics.DrawImage(Boxes, boxe3);
				graphics.DrawImage(Boxes, boxe4);
				graphics.DrawImage(Boxes, boxe5);
				graphics.DrawImage(Boxes, boxe6);
			}


			// change the bird image.
			reptile = (Bitmap *)Image::FromFile(L"./res/frame-5.png");

			graphics.ResetTransform();
			// calling RotateTransform to rotate pictrue of bird.
			graphics.RotateTransform(fill_Angle++, MatrixOrderAppend);
			// calling TranslateTransform to set new X, Y position to translate to new position.
			graphics.TranslateTransform(Xposition, Yposition, MatrixOrderAppend);
			// Draw bird with new rotation and position.
			graphics.DrawImage(reptile, -myRepitileRect.Width, -myRepitileRect.Height / 2, myRepitileRect.Width, myRepitileRect.Height);
		}
	}
	else // otherwise (the bird is not shot)
	{
		graphics.DrawImage(Boxes, boxe1);
		graphics.DrawImage(Boxes, boxe2);
		graphics.DrawImage(Boxes, boxe3);
		graphics.DrawImage(Boxes, boxe4);
		graphics.DrawImage(Boxes, boxe5);
		graphics.DrawImage(Boxes, boxe6);

		// drawing bird.
		graphics.DrawImage(reptile, myRepitileRect);			
	}
	//End draw to backbuffer bitmap buffer.

	//Swap buffers ie. push memory backbuffer to the screen frontbuffer.
	RECT reClip;
	::GetClipBox(dc, &reClip);
	left = reClip.left;
	top = reClip.top;
	width = reClip.right - reClip.left;
	height = reClip.bottom - reClip.top;
	::BitBlt(dc, left, top, width, height, hdcMem, left, top, SRCCOPY);

	::RestoreDC(hdcMem, nMemDC);
	::DeleteObject(hBitmap);
	::DeleteDC(hdcMem);
	
	// counter add one for flying bird.
	counter++;
	flyingCounter++;

	// Do not call CWnd::OnPaint() for painting messages
}






/*
* This functino is used to close windows to erase backgrond.
*/
BOOL CWnd::OnEraseBkgnd(CDC* pDC)
{
	return false;
}






/*
* This is a erase background handler.
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnEraseBkgnd(pDC);
}






/*
* Function : OnTimer()
* Description : This function is used to control bird every second.
* Parameter : UINT_PTR nIDEvent : Event ID.
* Return : Nothing
*/
void CWnd::OnTimer(UINT_PTR nIDEvent)
{
	// get Info of Windows.
	CRect rect;
	GetClientRect(rect);

	// random up or down
	int result = 0; // get random number.
	// generate random number.
	srand(time(NULL));
	result = rand() % 2 + 1;



	// if isHitGround flag is true.
	if (isHitGround == true)
	{
		Xposition = rect.left + 120;
		Yposition = rect.top + 50;
		isHitGround = false;
		isHit = false;
		flying = true;
		xueShow = true;
		start = false;
		isCrash = false;

		// reset all length1-length6.
		length1 = 50;
		length2 = 50;
		length3 = 50;
		length4 = 50;
		length5 = 50;
		length6 = 50;
	}
	else // isHitGround flag is false.
	{
		// if isHit flag is false.
		if (isHit == false)
		{
			if (goingRight == true)
			{
				Xposition += 8;
				//goingLeft = false;
			}
			else if (goingLeft == true)
			{
				Xposition -= 8;
				//goingRight = false;
			}
			
			// if the bird is running to right of window.
			if ((Xposition >= rect.right - 64) || (Yposition <= rect.top - 32) || (Xposition <= rect.left))
			{
				Xposition = rect.left + 120;
				Yposition = rect.top + 50;
			}

			// 20% width go to back Y position
			if (Yposition >= (rect.Width() * 0.2))
			{
				result = 2;
			}

			// fly pattern.
			if (result == 1)
			{
				goingUp = false;
				goingDown = true;

				Yposition += 8;
			}
			else if (result == 2)
			{
				goingUp = true;
				goingDown = false;

				Yposition -= 8;
			}
		}
		else // otherwise.
		{
			if (goingUp == true)
			{
				Xposition += 0;
				Yposition += 5;
			}
			else if (goingDown == true)
			{
				Xposition += 5;
				Yposition += 5;
			}
		}
	}

	// refresh the window
	InvalidateRect(&rect, 0);
}






/*
* This is a time handler 
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnTimer(nIDEvent);
}







/*
* Function : OnLButtonDown()
* Description : This function is used to handle left button down event.
* Parameter : UINT nFlags : flags.
*			  CPoint point : point of mouse (x point, y point).
* Return : Nothing
*/
void CWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	//check whether left click, and it click on image of bird.
	if (((point.x >= Xposition * widthRate) && (point.x <= (Xposition + 64) * widthRate)) && (point.y >= Yposition * heightRate) && (point.y <= (Yposition + 64) * heightRate))
	{
		// Change isHitFlag
		isHit = true;
		// play hittingSound when bird is hit.
		PlaySound(L"Sound/hittingSound.wav", NULL, SND_FILENAME | SND_ASYNC);		
	}
	else
	{	
		// play shootingSound when user missing shoot.
		PlaySound(L"Sound/shootingSound.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}






/*
* Function : OnLButtonDown()
* Description : This function is used to handle on left button down event.
* Parameter : UINT nFlags
			  CPoint point
* Return : Nothing
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}






/*
* Function : OnSetCursor()
* Description : This function is used to change image for cursor.
* Parameter : 
* Return : bool : true false.
*/
HCURSOR m_hCursor = LoadCursorFromFile(L"./res/AimAt.cur");
BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}





/*
* Function : LoadBirdImage()
* Description : This function is used to automatically load differnece iamges for boxes when game begins.
* Parameter : Nothing
* Return : Nothing
*/
void CChildView::LoadBirdImage(int counter)
{
	if (counter == 1)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-1.png");
	}
	else if (counter == 2)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-2.png");
	}
	else if (counter == 3)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-3.png");
	}
	else if (counter == 4)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-4.png");
	}
}






/*
* Function : LoadBirdImage()
* Description : This function is used to automatically load differnece iamges for boxes when game begins.
* Parameter : Nothing
* Return : Nothing
*/
void CChildView::LoadRotateBirdImage(int counter)
{
	if (counter == 1)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-1.png");
		reptile->RotateFlip(RotateNoneFlipX);
	}
	else if (counter == 2)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-2.png");
		reptile->RotateFlip(RotateNoneFlipX);
	}
	else if (counter == 3)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-3.png");
		reptile->RotateFlip(RotateNoneFlipX);
	}
	else if (counter == 4)
	{
		reptile = (Bitmap *)Image::FromFile(L"./res/frame-4.png");
		reptile->RotateFlip(RotateNoneFlipX);
	}
}





/*
* Function : IsCrashObject()
* Description : This function is used to automatically load differnece iamges when game begin.
* Parameter : Nothing
* Return : Nothing
*/
void CChildView::AutoLoadBoxeImage(void)
{
	int result = 0;

	srand(time(NULL));

	result = rand() % 4 + 1;

	switch (result)
	{
		case 1:
			{
				Boxes = (Bitmap *)Image::FromFile(L"./res/Cup.png");
			}
			break;
		case 2:
			{
				Boxes = (Bitmap *)Image::FromFile(L"./res/Wood-Boxes.png");
			}
			break;
		case 3:
			{
				Boxes = (Bitmap *)Image::FromFile(L"./res/box.png");
			}
			break;
		default:
			Boxes = (Bitmap *)Image::FromFile(L"./res/Wood-Boxes.png");
			break;
	}
}






/*
* Function : IsCrashObject()
* Description : This function is used to detect two objects whether it is crash.
* Parameter : x1 : first object of X point.
			  y1 : first object of Y point.
			  w1 : width of first object.
			  h1 : heigh of first object.
			  x2 : second object of X position.
			  y2 : second object of Y position.
			  w2 : width of second object.
			  y2 : heigh of second obkect.
			  whichBox : which box.
* Return : int : which box.
*/
int CChildView::IsCrashObject(int x1, int y1, int w1, int h1,
							  int x2, int y2, int w2, int h2, int whichBox)
{
		if (x1 >= x2 && x1 >= x2 + w2) {
			return -1;
		}
		else if (x1 <= x2 && x1 + w1 <= x2) {
			return -1;
		}
		else if (y1 >= y2 && y1 >= y2 + h2) {
			return -1;
		}
		else if (y1 <= y2 && y1 + h1 <= y2) {
			return -1;
		}

		Number += 50;
		return whichBox;
}





/*
* Function : rateWidthWindows()
* Description : This function is used to get rate of width when user change the size of windows.
* Parameter : int width: width of windows.
* Return : the rate of width.
*/
float CChildView::rateWidthWindows(int width)
{
	int originalWidth = 1420;
	float result = 0;

	// get final result.
	result = width / (float)originalWidth;

	// return result.
	return result;
}





/*
* Function : rateHeightWindows()
* Description : This function is used to get rate of height when user change the size of windows.
* Parameter : int width: height of windows.
* Return : the rate of height.
*/
float CChildView::rateHeightWindows(int height)
{
	int originalHeight = 655;
	float result = 0;

	// get final result.
	result = height / (float)originalHeight;

	// return result.
	return result;
}

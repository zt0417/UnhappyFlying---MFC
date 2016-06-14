
// UnhappyFlying.h : main header file for the UnhappyFlying application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CUnhappyFlyingApp:
// See UnhappyFlying.cpp for the implementation of this class
//

class CUnhappyFlyingApp : public CWinApp
{
public:
	ULONG_PTR gdiplusToken; // Global value for GDI+
public:
	CUnhappyFlyingApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUnhappyFlyingApp theApp;

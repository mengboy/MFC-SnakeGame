
// SnakeGame.h : SnakeGame Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSnakeGameApp:
// �йش����ʵ�֣������ SnakeGame.cpp
//

class CSnakeGameApp : public CWinAppEx
{
public:
	CSnakeGameApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnGameExit();
};

extern CSnakeGameApp theApp;

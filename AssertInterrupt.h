
// AssertInterrupt.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAssertInterruptApp:
// �йش����ʵ�֣������ AssertInterrupt.cpp
//

class CAssertInterruptApp : public CWinApp
{
public:
	CAssertInterruptApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAssertInterruptApp theApp;
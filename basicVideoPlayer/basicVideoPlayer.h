
// basicVideoPlayer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CbasicVideoPlayerApp:
// �� Ŭ������ ������ ���ؼ��� basicVideoPlayer.cpp�� �����Ͻʽÿ�.
//

class CbasicVideoPlayerApp : public CWinApp
{
public:
	CbasicVideoPlayerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CbasicVideoPlayerApp theApp;
// WheelLight.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CWheelLightApp:
// �� Ŭ������ ������ ���ؼ��� WheelLight.cpp�� �����Ͻʽÿ�.
//

class CWheelLightApp : public CWinApp
{
public:
	CWheelLightApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CWheelLightApp theApp;
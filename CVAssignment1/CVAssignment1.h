
// CVAssignment1.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CCVAssignment1App: 
// �аѾ\��@�����O�� CVAssignment1.cpp
//

class CCVAssignment1App : public CWinApp
{
public:
	CCVAssignment1App();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CCVAssignment1App theApp;
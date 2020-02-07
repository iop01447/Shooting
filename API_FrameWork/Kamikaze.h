#pragma once
#include "Obj.h"


class CKamikaze : public CObj
{
public:
	CKamikaze();
	~CKamikaze();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

private:
	int m_iColor[3];
};


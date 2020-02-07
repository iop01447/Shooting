#pragma once
#include "Obj.h"
class CShield_Monster :
	public CObj
{
public:
	CShield_Monster();
	virtual ~CShield_Monster();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

private:
	int m_iColor[3];

};


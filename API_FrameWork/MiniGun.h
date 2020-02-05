#pragma once
#include "Obj.h"
class CMiniGun :
	public CObj
{
public:
	CMiniGun();
	~CMiniGun();

	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

private:
	CObj*		m_pPlayer;
};


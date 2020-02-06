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

	void Shoot_Basic();

	CObj * CMiniGun::Create_Bullet(float x, float y);
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }
	void Set_Id(MINIGUN::ID _eId) { m_eId = _eId; }

private:
	list<CObj*>*	m_pBullet;
	CObj*			m_pPlayer;
	MINIGUN::ID		m_eId;
};


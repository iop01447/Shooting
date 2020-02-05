#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Obj.h"
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
	
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

private:
	CObj* Create_Bullet();
	CObj* Create_Bullet(BULLET::DIR _eDIr);

public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }

private:
	list<CObj*>*	m_pBullet;
	float			m_fDis;
	const int m_create_time{ 100 };
	DWORD m_old_time{ GetTickCount() };
};

#endif // !__PLAYER_H__

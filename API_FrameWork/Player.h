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
	CObj* Create_Bullet(float x, float y, BULLET::SHAPE _eShape);

public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }

public:
	void Update_Polygon();
	void Skill_1();

private:
	list<CObj*>*	m_pBullet;
	float			m_fDis;
	const DWORD		m_iBulletCreateTime;
	DWORD			m_OldTime;

	POINT			m_Points[4];

};

#endif // !__PLAYER_H__

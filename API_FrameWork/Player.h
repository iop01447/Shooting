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
	template <typename T>
	CObj* Create_Bullet(float x, float y, float angle, BULLET::SHAPE shape = BULLET::SHAPE::CIRCLE)
	{
		CObj* pObj = CAbstractFactory<T>::Create(x, y, angle);
		dynamic_cast<T*>(pObj)->Set_Shape(shape);
		pObj->Set_Color(52, 137, 235);
		pObj->Set_Pen_UnVisible();
		return pObj;
	}

public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }
	bool Can_Shoot_Bullet(DWORD _BulletcreateTime) { return (GetTickCount() - m_BulletOldTime) > _BulletcreateTime; }

public:
	void Update_Polygon();

public:
	void Draw_Star(HDC _DC, int _x, int _y);

public:
	void Skill_1();

private:
	list<CObj*>*	m_pBullet;
	float			m_fDis;
	const DWORD		m_iBulletCreateTime;
	DWORD			m_BulletOldTime;

	POINT			m_Points[4];
	POINT			m_StarPos[11];

	const DWORD		m_GazeMaxTime;
	DWORD			m_OldGazeTime;

	int				m_iSkillCnt;

	bool			m_bUnDead;
};

#endif // !__PLAYER_H__

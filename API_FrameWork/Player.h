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
		pObj->Set_Damage(m_iDamage);
		return pObj;
	}

public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }
	bool Can_Shoot_Bullet(DWORD _BulletcreateTime) { return (GetTickCount() - m_BulletOldTime) > _BulletcreateTime; }
	void Shoot_Bullet();

public:
	void Update_Polygon();

public:
	void Draw_Star(HDC _DC, int _x, int _y);

public:
	void Skill_1();

public:
	virtual void Collision(CObj* _obj, OBJID::ID _id);

private:
	list<CObj*>*	m_pBullet;
	float			m_fDis;
	const DWORD		m_iBulletCreateTime;
	DWORD			m_BulletOldTime;

	POINT			m_Points[4];
	POINT			m_StarPos[11];

	const DWORD		m_GazeMaxTime;
	DWORD			m_OldGazeTime;

	int				m_iSkillCnt; // 스킬을 사용할 수 있는 횟수
	int				m_iSkillLv;

	bool			m_bUnDead;
};

#endif // !__PLAYER_H__

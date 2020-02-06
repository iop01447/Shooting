#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__


#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();
public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pMonsterBullet = _pBullet; }
	CObj* Create_Bullet(BULLET::DIR _eDIr);
	CObj* Create_Bullet(BULLET::DIR _eDIr, float _Angle);

	void Bullet_Aoe();
public:
	void Set_Id(OBJID::ID _eId) { m_eId = _eId; }
	int KamiKaze();
private:
	OBJID::ID	m_eId;
	list<CObj*>*	m_pMonsterBullet;
};


#endif // !__MONSTER_H__

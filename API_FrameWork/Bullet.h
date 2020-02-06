#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__


#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	void Set_Dir(BULLET::DIR _eDir) { m_eDir = _eDir; }
	void Set_Shape(BULLET::SHAPE _eShape);

private:
	BULLET::DIR		m_eDir;
	BULLET::SHAPE	m_eShape;

};


#endif // !__BULLET_H__

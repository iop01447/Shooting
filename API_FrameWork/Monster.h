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
};


#endif // !__MONSTER_H__

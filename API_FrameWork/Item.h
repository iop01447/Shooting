#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	
	virtual void Collision(CObj* _obj, OBJID::ID _id) { m_bDead = true; }

public:
	ITEM::ID Get_Id() { return m_eId; }

private:
	ITEM::ID	m_eId;
};


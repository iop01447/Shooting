#pragma once
#include "Obj.h"
class CShotgun_Monster :
	public CObj
{
public:
	CShotgun_Monster();
	virtual ~CShotgun_Monster();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

public:
	CObj* Create_Bullet();
	void Set_Bullet(list<CObj*>* _pBullet) { m_pMonsterBullet = _pBullet; }
	void Set_Item(list<CObj*>* _pItem) { m_pItem = _pItem; }

	template <typename T>
	CObj* Create_Bullet(float _Angle)
	{
		CObj* pObj = CAbstractFactory<T>::Create(m_tInfo.fX, m_tInfo.fY, _Angle);
		return pObj;
	}

private:
	list<CObj*>*	m_pMonsterBullet;
	list<CObj*>*	m_pItem;
};


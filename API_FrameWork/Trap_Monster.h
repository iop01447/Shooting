#pragma once
#include "Obj.h"
class CTrap_Monster :
	public CObj
{
public:
	CTrap_Monster();
	virtual ~CTrap_Monster();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();
public:
	CObj * Create_Bullet();
	void Set_Bullet(list<CObj*>* _pBullet) { m_pMonsterBullet = _pBullet; }

	template <typename T>
	CObj* Create_Bullet(CObj*	_pTarget)
	{
		CObj* pObj = CAbstractFactory<T>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, _pTarget);
		return pObj;
	}

private:
	list<CObj*>*	m_pMonsterBullet;
};


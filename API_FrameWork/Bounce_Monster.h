#pragma once
#include "Obj.h"
class CBounce_Monster :
	public CObj
{
public:
	CBounce_Monster();
	virtual ~CBounce_Monster();
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
	CObj* Create_Bullet()
	{
		CObj* pObj = CAbstractFactory<T>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);
		return pObj;
	}
private:
	list<CObj*>*	m_pMonsterBullet;
};


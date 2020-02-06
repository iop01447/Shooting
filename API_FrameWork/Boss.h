#pragma once
#include "Obj.h"

#define ARM_HWIDTH 25.f
#define ARM_LENGTH 100.f	//∫∏Ω∫ ∆» ±Ê¿Ã
#define POSIN_HWIDTH  10.f
#define POSIN_HEIGHT 80.f
#define ARM_HWIDTH 25.f
#define MINIGUN_DIS (ARM_LENGTH+0.f)

class MiniGun;
class CBoss :
	public CObj
{
public:
	CBoss();
	virtual ~CBoss();

	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

	void Set_Boss(list<CObj*>* _pBoss) { m_pBoss = _pBoss; }
	void Set_Left(CObj* _pLeft) { m_pLeft = _pLeft; }
	void Set_Right(CObj* _pRight) { m_pRight = _pRight; }

	CObj* Create_Bullet(float x, float y);
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }

private:
	list<CObj*>*	m_pBullet;
	list<CObj*>*	 m_pBoss;
	CObj*			m_pPlayer;
	CObj*			m_pLeft;
	CObj*			m_pRight;
	float			m_fLeftAngle;
	float			m_fRightAngle;
};


#pragma once
#include "Obj.h"

#define ARM_HWIDTH 25.f
#define ARM_LENGTH 100.f	//∫∏Ω∫ ∆» ±Ê¿Ã
#define POSIN_HWIDTH  10.f
#define POSIN_HEIGHT 80.f
#define ARM_HWIDTH 25.f
#define MINIGUN_DIS (ARM_LENGTH+0.f)
#define BOSS_MAX_HP 200
#define BOSS_ICX 100

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

	void MiniGun_Update();
	void Rotate_Body(float _fAngle);
	void Rotate_Right(float _fAngle);
	void Rotate_Left(float _fAngle);

	void State_Ini();
	void State_P1_Idle();
	void State_P1_A1_Pre();
	void State_P1_A1_S1();
	void State_P1_A1_S2();
	void State_P1_A1_S3();
	void State_P2_Idle();
	

	void Shoot(float _fRAngle, float _fSpeed);

private:
	list<CObj*>*	m_pBullet;
	list<CObj*>*	 m_pBoss;
	CObj*			m_pPlayer;
	CObj*			m_pLeft;
	CObj*			m_pRight;
	float			m_fLeftAngle;
	float			m_fRightAngle;
	float			m_fLeftSpeed;
	float			m_fRightSpeed;
	BOSS::STATE		m_eState;
	BOSS::STATE		m_eStatePrev;
	int				m_iTick;
	//int				m_iTickStart;
};


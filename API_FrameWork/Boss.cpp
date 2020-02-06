#include "stdafx.h"
#include "Boss.h"
#include "Bullet.h"
#include "MiniGun.h"





CBoss::CBoss()
	:m_pPlayer(nullptr), m_pLeft(nullptr), m_pRight(nullptr), m_fLeftAngle(0.f), m_fRightAngle(0.f), 
	m_pBoss(nullptr), m_eState(BOSS::END), m_eStatePrev(BOSS::END),m_iTick(0), m_fLeftSpeed(0.f), m_fRightSpeed(0.f)
{
}


CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = 200.f;

	m_tInfo.iCX = 100.f;
	m_tInfo.iCY = 100.f;

	m_fSpeed = 1.f;
	m_fAngle = 270.f;
	m_fLeftAngle = 180.f;
	m_fRightAngle = 0.f;
	m_fAngleSpeed = 1.f;
	m_fLeftSpeed = -1.f;
	m_fRightSpeed = 1.f;

	m_iHp = BOSS_MAX_HP;
	
	m_eState = BOSS::P1_IDLE;
}

int CBoss::Update()
{
	if (m_eStatePrev != m_eState)
		m_iTick = 0;
	else
		++m_iTick;
	m_eStatePrev = m_eState;
	/*m_pLeft->Set_Pos()*/
	switch (m_eState)
	{
	case BOSS::P1_IDLE:
		State_P1_Idle();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
}

void CBoss::Render(HDC _DC)
{
	//Æ÷½Å
	MoveToEx(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle - 90.f)*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle - 90.f)*PI / 180.f) + POSIN_HEIGHT*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle - 90.f)*PI / 180.f) - POSIN_HEIGHT*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle + 90.f)*PI / 180.f) + POSIN_HEIGHT*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle + 90.f)*PI / 180.f) - POSIN_HEIGHT*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle + 90.f)*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle + 90.f)*PI / 180.f));

	//¿À¸¥ÆÈ
	MoveToEx(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle - 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle - 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fRightAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle - 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fRightAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle + 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fRightAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle + 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fRightAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle + 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle + 90.f)*PI / 180.f));

	//¿ÞÆÈ
	MoveToEx(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle - 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle - 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fLeftAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle - 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fLeftAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle + 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fLeftAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle + 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fLeftAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle + 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle + 90.f)*PI / 180.f));
	
	//¸öÃ¼
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	float fHalf_Diag = /*sqrtf(2.f)**/(m_tInfo.iCX/2);
	MoveToEx(_DC, m_tInfo.fX + fHalf_Diag*cosf((45.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((45.f + m_fAngle)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((135.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((135.f + m_fAngle)*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((225.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((225.f + m_fAngle)*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((315.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((315.f + m_fAngle)*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((45.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((45.f + m_fAngle)*PI / 180.f));

	fHalf_Diag /= 2.f;
	MoveToEx(_DC, m_tInfo.fX + fHalf_Diag*cosf((45.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((45.f + m_fAngle)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((135.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((135.f + m_fAngle)*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((225.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((225.f + m_fAngle)*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((315.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((315.f + m_fAngle)*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + fHalf_Diag*cosf((45.f + m_fAngle)*PI / 180.f), m_tInfo.fY - fHalf_Diag*sinf((45.f + m_fAngle)*PI / 180.f));

	//Ã¼·Â¹Ù
	

}

void CBoss::Release()
{
	SAFE_DELETE(m_pLeft);
	SAFE_DELETE(m_pRight);
}
CObj * CBoss::Create_Bullet(float x, float y)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(x, y);

	return pObj;
}

void CBoss::MiniGun_Update()
{
	m_pLeft->Set_Pos(m_tInfo.fX + MINIGUN_DIS*cosf(m_fLeftAngle*PI / 180.f), m_tInfo.fY - MINIGUN_DIS*sinf(m_fLeftAngle*PI / 180.f));
	m_pRight->Set_Pos(m_tInfo.fX + MINIGUN_DIS*cosf(m_fRightAngle*PI / 180.f), m_tInfo.fY - MINIGUN_DIS*sinf(m_fRightAngle*PI / 180.f));
}

void CBoss::Rotate_Body(float _fAngle)
{
	m_fAngle += _fAngle;
	m_fRightAngle += _fAngle;
	m_fLeftAngle += _fAngle;
	m_pLeft->Add_Angle(_fAngle);
	m_pRight->Add_Angle(_fAngle);
	MiniGun_Update();
}

void CBoss::Rotate_Right(float _fAngle)
{
	m_fRightAngle += _fAngle;
	m_pRight->Add_Angle(_fAngle);
	MiniGun_Update();
}

void CBoss::Rotate_Left(float _fAngle)
{
	m_fLeftAngle += _fAngle;
	m_pLeft->Add_Angle(_fAngle);
	MiniGun_Update();
}

void CBoss::State_P1_Idle()
{
	if (m_tInfo.fX <= 200 || m_tInfo.fX>=400)
		m_fSpeed *= -1;
	m_tInfo.fX += m_fSpeed;

	if (m_fAngle >= 300.f || m_fAngle <= 240.f)
		m_fAngleSpeed *= -1;
	if (m_fAngle-m_fRightAngle >= 300.f || m_fAngle-m_fRightAngle <= 240.f)
		m_fRightSpeed *= -1;
	if (m_fAngle - m_fLeftAngle >= 120.f || m_fAngle - m_fLeftAngle <= 60.f)
		m_fLeftSpeed *= -1;
	//Rotate_Body(m_fAngleSpeed/2.f);
	Rotate_Right(m_fRightSpeed);
	Rotate_Left(m_fLeftSpeed);
	if (m_iTick % 20 == 0)
	{
		dynamic_cast<CMiniGun*>(m_pLeft)->Shoot_Basic();
		dynamic_cast<CMiniGun*>(m_pRight)->Shoot_Basic();
	}

}

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
	m_tInfo.fX = 100.f;
	m_tInfo.fY = -200.f;

	m_tInfo.iCX = 0;
	m_tInfo.iCY = 0;

	m_fSpeed = 1.f;
	m_fAngle = 270.f;
	m_fLeftAngle = 180.f;
	m_fRightAngle = 0.f;
	m_fAngleSpeed = 1.f;
	m_fLeftSpeed = -1.f;
	m_fRightSpeed = 1.f;

	m_iHp = BOSS_MAX_HP;
	
	m_eState = BOSS::INI;
}

int CBoss::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_eStatePrev != m_eState)
		m_iTick = 0;
	else
		++m_iTick;
	m_eStatePrev = m_eState;

	//if (m_pLeft || m_pRight)	//양쪽 대포 다 안깨면 보스는 무적
	//	m_iHp = BOSS_MAX_HP;
	/*m_pLeft->Set_Pos()*/
	switch (m_eState)
	{
	case BOSS::INI:
		State_Ini();
		break;
	case BOSS::P1_IDLE:
		State_P1_Idle();
		break;
	case BOSS::P1_A1_PRE:
		State_P1_A1_Pre();
		break;
	case BOSS::P1_A1_S1:
		State_P1_A1_S1();
		break;
	case BOSS::P1_A1_S2:
		State_P1_A1_S2();
		break;
	case BOSS::P1_A1_S3:
		State_P1_A1_S3();
		break;
	case BOSS::P2_IDLE:
		State_P2_Idle();
		break;
	}
	if (!m_pLeft && !m_pRight)
	{
		m_tInfo.iCX = BOSS_ICX;
		m_tInfo.iCY = BOSS_ICX;
	}

	MiniGun_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
	if (m_pLeft) 
	{
		if (m_pLeft->Is_Dead())
			m_pLeft = nullptr;
	}
	if (m_pRight) 
	{
		if (m_pRight->Is_Dead())
			m_pRight = nullptr;
	}
	if (m_iHp <= 0)
	{
		m_bDead = true;	
	}
}

void CBoss::Render(HDC _DC)
{
	//포신
	MoveToEx(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle - 90.f)*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle - 90.f)*PI / 180.f) + POSIN_HEIGHT*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle - 90.f)*PI / 180.f) - POSIN_HEIGHT*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle + 90.f)*PI / 180.f) + POSIN_HEIGHT*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle + 90.f)*PI / 180.f) - POSIN_HEIGHT*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + POSIN_HWIDTH*cosf((m_fAngle + 90.f)*PI / 180.f), m_tInfo.fY - POSIN_HWIDTH*sinf((m_fAngle + 90.f)*PI / 180.f));

	//오른팔
	MoveToEx(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle - 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle - 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fRightAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle - 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fRightAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle + 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fRightAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle + 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fRightAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fRightAngle + 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fRightAngle + 90.f)*PI / 180.f));

	//왼팔
	MoveToEx(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle - 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle - 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fLeftAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle - 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fLeftAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle + 90.f)*PI / 180.f) + ARM_LENGTH*cosf(m_fLeftAngle*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle + 90.f)*PI / 180.f) - ARM_LENGTH*sinf(m_fLeftAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ARM_HWIDTH*cosf((m_fLeftAngle + 90.f)*PI / 180.f), m_tInfo.fY - ARM_HWIDTH*sinf((m_fLeftAngle + 90.f)*PI / 180.f));
	
	//몸체
	Ellipse(_DC, m_tInfo.fX-BOSS_ICX/2, m_tInfo.fY - BOSS_ICX / 2, m_tInfo.fX + BOSS_ICX / 2, m_tInfo.fY + BOSS_ICX / 2);
	float fHalf_Diag = /*sqrtf(2.f)**/(BOSS_ICX/2);
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

	//체력바
	Rectangle(_DC, WINCX-40, 30, WINCX-30, 300);
	RECT tHp = { WINCX - 40, 30 + ((float)(BOSS_MAX_HP - m_iHp) / (float)BOSS_MAX_HP)*(300-30),  WINCX - 30, 300 };
	this->Set_Color(255, 0, 0);
	FillRect(_DC, &tHp, m_Brush);
	this->Set_Color(255, 255, 255);

	

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
	if(m_pLeft)
		m_pLeft->Set_Pos(m_tInfo.fX + MINIGUN_DIS*cosf(m_fLeftAngle*PI / 180.f), m_tInfo.fY - MINIGUN_DIS*sinf(m_fLeftAngle*PI / 180.f));
	if(m_pRight)
		m_pRight->Set_Pos(m_tInfo.fX + MINIGUN_DIS*cosf(m_fRightAngle*PI / 180.f), m_tInfo.fY - MINIGUN_DIS*sinf(m_fRightAngle*PI / 180.f));
}

void CBoss::Rotate_Body(float _fAngle)
{
	m_fAngle += _fAngle;
	m_fRightAngle += _fAngle;
	m_fLeftAngle += _fAngle;
	if(m_pLeft)
		m_pLeft->Add_Angle(_fAngle);
	if(m_pRight)
		m_pRight->Add_Angle(_fAngle);
	MiniGun_Update();
}

void CBoss::Rotate_Right(float _fAngle)
{
	m_fRightAngle += _fAngle;
	if (m_pRight)
		m_pRight->Add_Angle(_fAngle);
	MiniGun_Update();
}

void CBoss::Rotate_Left(float _fAngle)
{
	m_fLeftAngle += _fAngle;
	if (m_pLeft)
		m_pLeft->Add_Angle(_fAngle);
	MiniGun_Update();
}

void CBoss::State_P1_Idle()
{
	//if (m_pLeft == nullptr && m_pRight == nullptr && m_tInfo.fX==300.f) //페이즈2 조건
	//{
	//	m_eState = BOSS::P2_IDLE;
	//	/*m_tRect.top = m_tInfo.fY - BOSS_ICX / 2;
	//	m_tRect.left = m_tInfo.fX - BOSS_ICX / 2;
	//	m_tRect.right = m_tInfo.fX + BOSS_ICX / 2;
	//	m_tRect.bottom = m_tInfo.fY + BOSS_ICX / 2;*/
	//	
	//	return;
	//}
	if (m_iTick >= 7 * 60) //Attack1 조건
	{
		m_eState = BOSS::P1_A1_PRE;
		return;
	}
	if (m_tInfo.fX <= 200 || m_tInfo.fX>=400)
		m_fSpeed *= -1;
	m_tInfo.fX += m_fSpeed;

	if (m_fAngle >= 300.f || m_fAngle <= 240.f)
		m_fAngleSpeed *= -1;
	if (m_fAngle-m_fRightAngle >= 320.f || m_fAngle-m_fRightAngle <= 240.f)
		m_fRightSpeed *= -1;
	if (m_fAngle - m_fLeftAngle >= 120.f || m_fAngle - m_fLeftAngle <= 40.f)
		m_fLeftSpeed *= -1;
	//Rotate_Body(m_fAngleSpeed/2.f);
	Rotate_Right(m_fRightSpeed);
	Rotate_Left(m_fLeftSpeed);
	if (m_iTick % 30 == 0)
	{
		if (m_pLeft)
			dynamic_cast<CMiniGun*>(m_pLeft)->Shoot_Basic();
		if (m_pRight)
			dynamic_cast<CMiniGun*>(m_pRight)->Shoot_Basic();
	}
	if (m_iTick % 60 == 0)
	{
		Shoot(0.f, 7.f);
		Shoot(45.f, 7.f);
		Shoot(-45.f, 7.f);
	}

}

void CBoss::State_P1_A1_Pre()
{
	bool flagX = false, flagY = false, flagA = false;
	if (m_tInfo.fX < 400.f)
		m_tInfo.fX += 2.f;
	else if (m_tInfo.fX > 402.f)
		m_tInfo.fX -= 2.f;
	else
	{
		m_tInfo.fX = 400.f;
		flagX = true;
	}
	if (m_tInfo.fY < 150.f)
		m_tInfo.fY += 1.f;
	else if (m_tInfo.fY > 152.f)
		m_tInfo.fY -= 1.f;
	else
	{
		m_tInfo.fY = 150.f;
		flagY = true;
	}
	if (m_fAngle > 240.f)
		Rotate_Body(-1.f);
	else if (m_fAngle < 238.f)
		Rotate_Body(1.f);
	else
		flagA = true;
	if (flagX == true && flagY == true && flagA == true)
		m_eState = BOSS::P1_A1_S1;
}

void CBoss::State_P1_A1_S1()
{
	bool flagL = false, flagR = false;
	if (m_fAngle - m_fLeftAngle < 120.f)
		Rotate_Left(-1.f);
	else
		flagL = true;
	if (m_fAngle - m_fRightAngle > 240.f)
		Rotate_Right(1.f);
	else
		flagR = true;
	if (flagL == true && flagR == true)
	{
		m_eState = BOSS::P1_A1_S2;
		if(m_pLeft)
			dynamic_cast<CMiniGun*>(m_pLeft)->Set_State(MINIGUN::LOCKON);
		if(m_pRight)
			dynamic_cast<CMiniGun*>(m_pRight)->Set_State(MINIGUN::LOCKON);
	}
}

void CBoss::State_P1_A1_S2()
{
	if (m_iTick % 60 == 0)
		if (m_pLeft)
			dynamic_cast<CMiniGun*>(m_pLeft)->Shoot_Basic(7.f);
	if (m_iTick % 60 == 30)
		if (m_pRight)
			dynamic_cast<CMiniGun*>(m_pRight)->Shoot_Basic(7.f);
	Rotate_Body(4.f);
	if(/*m_iTick%300/100!=1 &&*/ m_iTick%4==0)
		Shoot(0.0f, 3.f);
	if (m_iTick >= 600 && m_iTick < 900)
	{
		/*if (m_tInfo.fX > 300.f)
			m_tInfo.fX -= 1.f;
		else
			m_tInfo.fX = 300.f;
		if (m_tInfo.fY < 200.f)
			m_tInfo.fY += 0.5f;
		else
			m_tInfo.fY = 200.f;*/
		m_tInfo.fX -= 1.f;
		m_tInfo.fY += 0.5f;
	}
	if (m_iTick >= 900 && m_iTick < 1200)
	{		
			m_tInfo.fY -= 0.5f;	
	}
	if (m_iTick >= 1200 && m_iTick<1500)
	{
		m_tInfo.fX += 1.f;
		m_tInfo.fY += 0.5f;
	}
	if(m_iTick>=1500 && m_iTick<1700)
	{
		if (m_tInfo.fX > 300.f)
		m_tInfo.fX -= 1.f;
		else
		m_tInfo.fX = 300.f;
		if (m_tInfo.fY > 200.f)
		m_tInfo.fY -= 0.5f;
		else
		m_tInfo.fY = 200.f;
	}
	if (m_iTick >= 1700)
	{
		m_eState = BOSS::P1_A1_S3;
		if (m_pLeft)
			dynamic_cast<CMiniGun*>(m_pLeft)->Set_State(MINIGUN::NORMAL);
		if (m_pRight)
			dynamic_cast<CMiniGun*>(m_pRight)->Set_State(MINIGUN::NORMAL);
	}
}

void CBoss::State_P1_A1_S3()
{
	//go to idle
	if (((int)m_fAngle + 360*10000) % 360 != 270.f)
		Rotate_Body(2.f);
	else
		m_fAngle = 270.f;
	if (m_fAngle == 270.f)
	{
		if (((int)m_fLeftAngle + 360 * 100000) %360 < 180)
			Rotate_Left(2.f);
		else
			m_fLeftAngle = 180.f;
		if (((int)m_fRightAngle + 360 * 100000) %360 > 0)
			Rotate_Right(-2.f);
		else
			m_fRightAngle = 0.f;
	}
	if (m_fAngle == 270.f && m_fLeftAngle == 180.f && m_fRightAngle == 0.f)
	{
		if (m_pLeft)
		{
			if (((int)(m_pLeft->Get_Angle() - 270.f)+ 360 * 100000) % 360 <2)
			{
				m_pLeft->Set_Angle(270.f);
			}
			else if (((int)(m_pLeft->Get_Angle() - 270.f) + 360 * 100000) % 360 >= 180)
			{
				m_pLeft->Add_Angle(2.f);
			}
			else
				m_pLeft->Add_Angle(-2.f);
		}
		if (m_pRight)
		{
			if (((int)(m_pRight->Get_Angle() - 270.f) + 360 * 100000) % 360 <2)
			{
				m_pRight->Set_Angle(270.f);
			}
			else if (((int)(m_pRight->Get_Angle() - 270.f) + 360 * 100000) % 360 >= 180)
			{
				m_pRight->Add_Angle(2.f);
			}
			else
				m_pRight->Add_Angle(-2.f);
		}
	}
	/*if (m_pRight && m_pLeft && m_pRight->Get_Angle() == 270.f && m_pLeft->Get_Angle() == 270.f)
	{
		m_eState = BOSS::P1_IDLE;
	}*/
	if ((!m_pRight || m_pRight->Get_Angle() == 270.f) && (!m_pLeft || m_pLeft->Get_Angle() == 270.f)&& m_fLeftAngle==180.f && m_fRightAngle == 0.f)
	{
		m_eState = BOSS::P1_IDLE;
	}

}

void CBoss::State_Ini()
{
	if (m_tInfo.fX >= 300)
	{
		m_eState = BOSS::P1_IDLE;
		return;
	}
	m_tInfo.fX += 1.f;
	m_tInfo.fY += 2.f;
}

void CBoss::State_P2_Idle()
{
	
}

void CBoss::Shoot(float _fRAngle, float _fSpeed)
{
	m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX  + POSIN_HEIGHT*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - POSIN_HEIGHT*sinf(m_fAngle*PI / 180.f)));
	m_pBullet->back()->Set_Speed(_fSpeed);
	m_pBullet->back()->Set_Angle(m_fAngle + _fRAngle);
	if (!m_pLeft)
	{
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + POSIN_HEIGHT*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - POSIN_HEIGHT*sinf(m_fAngle*PI / 180.f)));
		m_pBullet->back()->Set_Speed(_fSpeed);
		m_pBullet->back()->Set_Angle(m_fAngle + _fRAngle+30.f);
	}
	if (!m_pRight)
	{
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + POSIN_HEIGHT*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - POSIN_HEIGHT*sinf(m_fAngle*PI / 180.f)));
		m_pBullet->back()->Set_Speed(_fSpeed);
		m_pBullet->back()->Set_Angle(m_fAngle + _fRAngle - 30.f);
	}
}

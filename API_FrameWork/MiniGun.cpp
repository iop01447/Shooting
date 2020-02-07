#include "stdafx.h"
#include "MiniGun.h"
#include "Bullet.h"
#include "RotatableBullet.h"

#define MINI_LENGTH 60.f
#define MINI_HWIDTH 5.f
#define MINI_HDIS 10.f
#define MINI_MAXHP 400


CMiniGun::CMiniGun()
	:m_pPlayer(nullptr)
{
}


CMiniGun::~CMiniGun()
{
}

void CMiniGun::Initialize()
{
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_fAngle = 270.f;

	m_iHp = MINI_MAXHP;
	m_eState = MINIGUN::NORMAL;

}

int CMiniGun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	/*if ((int)m_fAngle % 20 == 0)
		Shoot_Basic();*/
	switch (m_eState)
	{
	case MINIGUN::NORMAL:
		break;
	case MINIGUN::LOCKON:
		State_LockOn();
		break;
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMiniGun::Late_Update()
{
	if (0 >= m_iHp)
		m_bDead = true;

}

void CMiniGun::Render(HDC _DC)
{
	POINT tBuf[4] = {};
	
	tBuf[0] = { (LONG)(m_tInfo.fX + (MINI_HDIS + MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f)),(LONG)(m_tInfo.fY - (MINI_HDIS + MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f)) };
	tBuf[1] = { (LONG)(m_tInfo.fX + (MINI_HDIS + MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f)),(LONG)(m_tInfo.fY - (MINI_HDIS + MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)) };
	tBuf[2] = { (LONG)(m_tInfo.fX + (MINI_HDIS - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f)),(LONG)(m_tInfo.fY - (MINI_HDIS - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)) };
	tBuf[3] = { (LONG)(m_tInfo.fX + (MINI_HDIS - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f)),(LONG)(m_tInfo.fY - (MINI_HDIS - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f)) };
	Polygon(_DC, tBuf, 4);

	
	tBuf[0] = { (LONG)(m_tInfo.fX + ((-MINI_HDIS) + MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f)),(LONG)(m_tInfo.fY - ((-MINI_HDIS) + MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f)) };
	tBuf[1] = { (LONG)(m_tInfo.fX + ((-MINI_HDIS) + MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f)),(LONG)(m_tInfo.fY - ((-MINI_HDIS) + MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)) };
	tBuf[2] = { (LONG)(m_tInfo.fX + ((-MINI_HDIS) - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f)),(LONG)(m_tInfo.fY - ((-MINI_HDIS) - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)) };
	tBuf[3] = { (LONG)(m_tInfo.fX + ((-MINI_HDIS) - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f)),(LONG)(m_tInfo.fY - ((-MINI_HDIS) - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f)) };
	Polygon(_DC, tBuf, 4);


	//¸öÃ¼
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//Ã¼·Â¹Ù
	if (m_eId == MINIGUN::LEFT)
	{
		Rectangle(_DC, WINCX-60, 30, WINCX-50, 150);
		RECT tHp = { WINCX - 60, 30 + ((float)(MINI_MAXHP - m_iHp) / (float)MINI_MAXHP)*(150 - 30),  WINCX - 50, 150 };
		this->Set_Color(255, 0, 0);
		FillRect(_DC, &tHp, m_Brush);
		this->Set_Color(255, 255, 255);

	}
	else
	{
		Rectangle(_DC, WINCX - 60, 180, WINCX - 50, 300);
		RECT tHp = { WINCX - 60, 180 + ((float)(MINI_MAXHP - m_iHp) / (float)MINI_MAXHP)*(150 - 30),  WINCX - 50, 300 };
		this->Set_Color(255, 0, 0);
		FillRect(_DC, &tHp, m_Brush);
		this->Set_Color(255, 255, 255);

	}

}

void CMiniGun::Release()
{
}

void CMiniGun::Shoot_Basic()
{
	m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + (MINI_HDIS)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)));
	m_pBullet->back()->Set_Speed(5.f);
	m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + (MINI_HDIS)*cosf((m_fAngle + 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS)*sinf((m_fAngle + 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)));
	m_pBullet->back()->Set_Speed(5.f);
}
void CMiniGun::Shoot_Basic(float _fSpeed)
{
	m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + (MINI_HDIS)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)));
	m_pBullet->back()->Set_Speed(_fSpeed);
	m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + (MINI_HDIS)*cosf((m_fAngle + 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS)*sinf((m_fAngle + 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)));
	m_pBullet->back()->Set_Speed(_fSpeed);
}
CObj * CMiniGun::Create_Bullet(float x, float y)
{
	CObj* pObj = CAbstractFactory<CRotatableBullet>::Create(x, y, m_fAngle);
	//dynamic_cast<CBullet*>(pObj)->Set_Shape(BULLET::SHAPE::CIRCLE);
	pObj->Set_Color(225, 200, 0);
	pObj->Set_Pen_UnVisible();

	return pObj;
}

void CMiniGun::State_LockOn()
{
	float fPlayerY = m_pTarget->Get_Info().fY;
	float fPlayerX = m_pTarget->Get_Info().fX;
	m_fAngle = atanf((fPlayerY - m_tInfo.fY) / (fPlayerX - m_tInfo.fX));

	if (fPlayerX - m_tInfo.fX < 0)
	{
		if (fPlayerY - m_tInfo.fY < 0)
		{
			m_fAngle = 180.f - atanf((fPlayerY - m_tInfo.fY) / (fPlayerX - m_tInfo.fX)) * 180 / PI;
		}
		else
		{
			m_fAngle = 180.f - atanf((fPlayerY - m_tInfo.fY) / (fPlayerX - m_tInfo.fX)) * 180 / PI;
		}
	}
	else
	{
		if (fPlayerY - m_tInfo.fY < 0)
		{
			m_fAngle = -atanf((fPlayerY - m_tInfo.fY) / (fPlayerX - m_tInfo.fX)) * 180 / PI;
		}
		else
		{
			m_fAngle = -atanf((fPlayerY - m_tInfo.fY) / (fPlayerX - m_tInfo.fX)) * 180 / PI;
		}
	}
}

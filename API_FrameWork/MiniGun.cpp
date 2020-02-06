#include "stdafx.h"
#include "MiniGun.h"
#include "Bullet.h"

#define MINI_LENGTH 60.f
#define MINI_HWIDTH 5.f
#define MINI_HDIS 10.f
#define MINI_MAXHP 100


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

}

int CMiniGun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	/*if ((int)m_fAngle % 20 == 0)
		Shoot_Basic();*/
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
	//포신1
	MoveToEx(_DC, m_tInfo.fX + (MINI_HDIS+MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f), m_tInfo.fY - (MINI_HDIS+MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + (MINI_HDIS+MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS+MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + (MINI_HDIS - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + (MINI_HDIS - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f), m_tInfo.fY - (MINI_HDIS - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f));

	//포신2
	MoveToEx(_DC, m_tInfo.fX + ((-MINI_HDIS) + MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f), m_tInfo.fY - ((-MINI_HDIS) + MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f), nullptr);
	LineTo(_DC, m_tInfo.fX + ((-MINI_HDIS) + MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - ((-MINI_HDIS) + MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ((-MINI_HDIS) - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - ((-MINI_HDIS) - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f));
	LineTo(_DC, m_tInfo.fX + ((-MINI_HDIS) - MINI_HWIDTH)*cosf((m_fAngle - 90.f)*PI / 180.f), m_tInfo.fY - ((-MINI_HDIS) - MINI_HWIDTH)*sinf((m_fAngle - 90.f)*PI / 180.f));


	//몸체
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//체력바
	if (m_eId == MINIGUN::LEFT)
	{
		Rectangle(_DC, 50, 30, 60, 150);
		RECT tHp = { 50, 30 + ((float)(MINI_MAXHP - m_iHp) / (float)MINI_MAXHP)*(150 - 30), 60, 150 };
		FillRect(_DC, &tHp, CreateSolidBrush(RGB(255, 0, 0)));
	}
	else
	{
		Rectangle(_DC, 50, 180, 60, 300);
		RECT tHp = { 50, 180 + ((float)(MINI_MAXHP - m_iHp) / (float)MINI_MAXHP)*(150 - 30), 60, 300 };
		FillRect(_DC, &tHp, CreateSolidBrush(RGB(255, 0, 0)));
	}

}

void CMiniGun::Release()
{
}

void CMiniGun::Shoot_Basic()
{
	m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + (MINI_HDIS)*cosf((m_fAngle - 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS)*sinf((m_fAngle - 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)));
	m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX + (MINI_HDIS)*cosf((m_fAngle + 90.f)*PI / 180.f) + MINI_LENGTH*cosf(m_fAngle*PI / 180.f), m_tInfo.fY - (MINI_HDIS)*sinf((m_fAngle + 90.f)*PI / 180.f) - MINI_LENGTH*sinf(m_fAngle*PI / 180.f)));
	
}
CObj * CMiniGun::Create_Bullet(float x, float y)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(x, y, m_fAngle);

	return pObj;
}

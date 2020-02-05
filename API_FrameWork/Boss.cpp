#include "stdafx.h"
#include "Boss.h"





CBoss::CBoss()
	:m_pPlayer(nullptr), m_pLeft(nullptr), m_pRight(nullptr), m_fLeftAngle(0.f), m_fRightAngle(0.f), m_pBoss(nullptr)
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

	m_fSpeed = 5.f;
	m_fAngle = 270.f;
	m_fLeftAngle = 180.f;
	m_fRightAngle = 0.f;
}

int CBoss::Update()
{
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
}

void CBoss::Release()
{
	SAFE_DELETE(m_pLeft);
	SAFE_DELETE(m_pRight);
}

#include "stdafx.h"
#include "MiniGun.h"

#define MINI_LENGTH 50.f
#define MINI_HWIDTH 5.f
#define MINI_HDIS 10.f


CMiniGun::CMiniGun()
	:m_pPlayer(nullptr)
{
}


CMiniGun::~CMiniGun()
{
}

void CMiniGun::Initialize()
{
	m_tInfo.iCX = 40.f;
	m_tInfo.iCY = 40.f;

	m_fAngle = 270.f;

}

int CMiniGun::Update()
{
	
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMiniGun::Late_Update()
{
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
}

void CMiniGun::Release()
{
}

#include "stdafx.h"
#include "Kamikaze.h"

CKamikaze::CKamikaze()
{
}


CKamikaze::~CKamikaze()
{
}

void CKamikaze::Initialize()
{
	m_tInfo.fX = float(WINCX/2);
	m_tInfo.fY = 0.f;
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_fSpeed = 5.f;

	Set_Color(255, 0, 0);
	Set_Pen_UnVisible();
}

int CKamikaze::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	int iTime = rand(), iX;

	float fX = 0.f, fY = 0.f, fDis = 0.f;
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CKamikaze::Late_Update()
{
}

void CKamikaze::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CKamikaze::Release()
{
}
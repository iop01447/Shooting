#include "stdafx.h"
#include "Rect.h"


CRect::CRect()
	: m_eDir(BULLET::DIR_END)
{
}


CRect::~CRect()
{
	Release();
}

void CRect::Initialize()
{
	m_tInfo.iCX = 15;
	m_tInfo.iCY = 15;
	m_fSpeed = 10.f;

	//총알떠는거 싫어서 고정값.
	m_fAngle = 45.f;

	Set_Color(0, 230, 100);
}

int CRect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_fAngle += 90.f;
	m_fSpeed += 5.f;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CRect::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CRect::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CRect::Release()
{
}
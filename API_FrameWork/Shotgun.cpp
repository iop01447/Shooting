#include "stdafx.h"
#include "Shotgun.h"

CShotgun::CShotgun()
	: m_eDir(BULLET::DIR_END)
{
}


CShotgun::~CShotgun()
{
	Release();
}

void CShotgun::Initialize()
{
	m_tInfo.iCX = 15;
	m_tInfo.iCY = 15;
	m_fSpeed = 10.f;

	//총알떠는거 싫어서 고정값.
	m_fAngle = 45.f;
}

int CShotgun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CShotgun::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CShotgun::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShotgun::Release()
{
}


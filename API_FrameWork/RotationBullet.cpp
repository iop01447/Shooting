#include "stdafx.h"
#include "RotationBullet.h"


CRotationBullet::CRotationBullet()
	: m_fRotAngle(0.f), m_fRotDis(0.f), m_fRotSpeed(0.f), m_bStart(true)
{
	ZeroMemory(&m_tCenter, sizeof(m_tCenter));
}


CRotationBullet::~CRotationBullet()
{
}

void CRotationBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;
	m_fSpeed = 10.f;

	m_fRotSpeed = 50.f;
	m_fRotDis = 20.f;
	m_iDamage = 20.f;

	m_bStart = true;
}

int CRotationBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bStart)
	{
		m_bStart = false;

		m_fRotAngle = m_fAngle;
		m_tCenter.x = (LONG)m_tInfo.fX;
		m_tCenter.y = (LONG)m_tInfo.fY;
	}

	m_fRotDis += m_fSpeed;
	m_fRotAngle += m_fRotSpeed;

	m_tInfo.fX = m_tCenter.x + cosf(m_fRotAngle * PI / 180.f) * m_fRotDis;
	m_tInfo.fY = m_tCenter.y - sinf(m_fRotAngle * PI / 180.f) * m_fRotDis;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CRotationBullet::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CRotationBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CRotationBullet::Release()
{
}

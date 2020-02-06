#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDir(BULLET::DIR_END), m_eShape(BULLET::CIRCLE)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.iCX = 15;
	m_tInfo.iCY = 15;

	m_fSpeed = 10.f;
	m_iDamage = 1;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//m_tInfo.fY -= m_fSpeed;
	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}

void CBullet::Set_Shape(BULLET::SHAPE _eShape)
{
	m_eShape = _eShape;

	switch (m_eShape)
	{
	case BULLET::SHAPE::CIRCLE:
		m_tInfo.iCX = 15;
		m_tInfo.iCY = 15;
		break;
	case BULLET::SHAPE::ELLIPSE:
		m_tInfo.iCX = 10;
		m_tInfo.iCY = 30;
		m_tInfo.fY -= 5;
		break;
	}
}

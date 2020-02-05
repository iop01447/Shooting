#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDir(BULLET::END)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;

	m_fSpeed = 5.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;


	//switch (m_eDir)
	//{
	//case BULLET::LEFT:
	//	m_tInfo.fX -= m_fSpeed;
	//	break;
	//case BULLET::RIGHT:
	//	m_tInfo.fX += m_fSpeed;
	//	break;
	//case BULLET::UP:
	//	m_tInfo.fY -= m_fSpeed;
	//	break;
	//case BULLET::DOWN:
	//	m_tInfo.fY += m_fSpeed;
	//	break;
	//}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (100 >= m_tRect.top || 100 >= m_tRect.left
		|| WINCX - 100 <= m_tRect.right || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}

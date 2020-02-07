#include "stdafx.h"
#include "Bounce_Ball.h"


CBounce_Ball::CBounce_Ball()
{
}


CBounce_Ball::~CBounce_Ball()
{
}

void CBounce_Ball::Initialize()
{
	m_tInfo.iCX = 15;
	m_tInfo.iCY = 15;

	m_fSpeed = 7.f;

	Set_Color(255, 255, 0);
}

int CBounce_Ball::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_iTime >= 975) //15ÃÊ
	{
		m_bDead = true;
	}
	//m_tInfo.fY -= m_fSpeed;
	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();
	m_iTime++;
	return OBJ_NOEVENT;
}

void CBounce_Ball::Late_Update()
{
	if (25 >= m_tRect.top ||  WINCY - 25 <= m_tRect.bottom)
		m_fAngle *= -1;
	else if (25 >= m_tRect.left || WINCX - 25 <= m_tRect.right)
	{
		m_fAngle *= -1;
		m_fSpeed *= -1;
	}
}

void CBounce_Ball::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBounce_Ball::Release()
{
}

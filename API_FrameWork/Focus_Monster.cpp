#include "stdafx.h"
#include "Focus_Monster.h"
#include "Bullet.h"



CFocus_Monster::CFocus_Monster()
{
}


CFocus_Monster::~CFocus_Monster()
{
}

void CFocus_Monster::Initialize()
{
	m_tInfo.fX = float(WINCX / 2);
	m_tInfo.fY = 1.f;
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_fSpeed = 2.5f;
}

int CFocus_Monster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	int iTime = rand();

	if (m_tInfo.fY >= 250)
	{
		if (m_tInfo.fX < m_pTarget->Get_Info().fX)
		{
			m_tInfo.fX += m_fSpeed;
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
	else
	{
		float fX = 0.f, fY = 0.f, fDis = 0.f;
		fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
		fDis = sqrtf(fX * fX + fY * fY);
		m_fAngle = acosf(fX / fDis) * 180.f / PI;

		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			m_fAngle *= -1.f;

		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	}
	//////////////총알발사 --> 하드코딩 수정필요
	if (iTime % 1300 >= 31 && iTime % 1300 <= 80) // 일반공격
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>());
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CFocus_Monster::Late_Update()
{
}

void CFocus_Monster::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CFocus_Monster::Release()
{
}
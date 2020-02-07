#include "stdafx.h"
#include "Bounce_Monster.h"
#include "Bounce_Ball.h"

CBounce_Monster::CBounce_Monster()
{
}


CBounce_Monster::~CBounce_Monster()
{
}

void CBounce_Monster::Initialize()
{
	m_tInfo.fX = float(WINCX / 2);
	m_tInfo.fY = 1.f;
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;
	m_iHp = 10;       //몬스터 최대 체력
	m_fSpeed = 2.f;

	Set_Color(255, 255, 0);
}

int CBounce_Monster::Update()
{
	if (m_bDead)
	{
		m_pMonsterBullet->clear();
		return OBJ_DEAD;
	}

	int iTime = rand();

	Monster_move(300);

	float fX = 0.f, fY = 0.f, fDis = 0.f;
	//////////////att
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	//////////////총알발사 --> 하드코딩 수정필요
	if (iTime % 650 >= 0 && iTime % 650 <= 7 && m_tInfo.fY >= 25) // 일반공격
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CBounce_Ball>());
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBounce_Monster::Late_Update()
{
	if (0 >= m_iHp)
	{
		m_bDead = true;
	}
}

void CBounce_Monster::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBounce_Monster::Release()
{
}
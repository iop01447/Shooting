#include "stdafx.h"
#include "Focus_Monster.h"
#include "Bullet.h"
#include "Item.h"



CFocus_Monster::CFocus_Monster()
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
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
	m_iHp = 15;       //몬스터 최대 체력

	m_fSpeed = 2.0f;

	Set_Color(100, 160, 120);
}

int CFocus_Monster::Update()
{
	if (m_bDead) {
		m_pItem->emplace_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY));
		return OBJ_DEAD;
	}

	int iTime = rand();
	float fX = 0.f, fY = 0.f, fDis = 0.f;
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	if (m_tInfo.fY >= 150) { ; }
	else
	{
		m_tInfo.fY += m_fSpeed;
	}
	//////////////총알발사
	if (iTime % 650 >= 0 && iTime % 650 <= 20 && m_tInfo.fY >= 150) // 일반공격
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>());
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CFocus_Monster::Late_Update()
{
	if (0 >= m_iHp)		{	m_bDead = true;	}
	
	m_tPosin.x = LONG(m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * 50.f);
	m_tPosin.y = LONG(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * 50.f);
}

void CFocus_Monster::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_DC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_DC, (int)m_tPosin.x, (int)m_tPosin.y);
}

void CFocus_Monster::Release()
{
}
#include "stdafx.h"
#include "Shotgun_Monster.h"
#include "Bullet.h"
#include "Item.h"
#include "AbstractFactory.h"

CShotgun_Monster::CShotgun_Monster()
{
}


CShotgun_Monster::~CShotgun_Monster()
{
}


void CShotgun_Monster::Initialize()
{
	m_tInfo.fX = float(WINCX / 2);
	m_tInfo.fY = 1.f;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_iHp = 25;       //몬스터 최대 체력
	m_fSpeed = 3.0f;

	Set_Color(120, 150, 120);
}

int CShotgun_Monster::Update()
{
	if (m_bDead) {
		m_pItem->emplace_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY));
		return OBJ_DEAD;
	}

	int iTime = rand();

	float fX = 0.f, fY = 0.f, fDis = 0.f;

	Monster_move(150);

	//////att
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;


	//////////////총알발사
	if (iTime % 650 >= 0 && iTime % 650 <= 6)
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle + 15.f));
		m_pMonsterBullet->emplace_back(Create_Bullet<CBullet>(m_fAngle - 15.f));
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CShotgun_Monster::Late_Update()
{
	if (0 >= m_iHp)
		m_bDead = true;
}

void CShotgun_Monster::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShotgun_Monster::Release()
{
}

CObj * CShotgun_Monster::Create_Bullet()
{
	return nullptr;
}

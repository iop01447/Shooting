#include "stdafx.h"
#include "Trap_Monster.h"
#include "Trap.h"


CTrap_Monster::CTrap_Monster()
{
}


CTrap_Monster::~CTrap_Monster()
{
}


void CTrap_Monster::Initialize()
{
	m_tInfo.fX = float(WINCX / 2);
	m_tInfo.fY = 1.f;
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;
	m_iHp = 20;       //몬스터 최대 체력

	m_fSpeed = 4.f;
}

int CTrap_Monster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	int iTime = rand();

	float fX = 0.f, fY = 0.f, fDis = 0.f;

	Monster_move(250);

	//////att
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;


	//////////////총알발사
	if (iTime % 650 >= 0 && iTime % 650 <= 5)
	{
		m_pMonsterBullet->emplace_back(Create_Bullet<CTrap>(m_pTarget));
		m_pMonsterBullet->back()->Set_Color(255, 0, 0);
		m_pMonsterBullet->back()->Set_Pen_UnVisible();
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CTrap_Monster::Late_Update()
{
	if (0 >= m_iHp) { m_bDead = true; }
}

void CTrap_Monster::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTrap_Monster::Release()
{
}
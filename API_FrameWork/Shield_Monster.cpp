#include "stdafx.h"
#include "Shield_Monster.h"
#include "Bullet.h"
#include "CollisionMgr.h"
#include "Item.h"

CShield_Monster::CShield_Monster()
{
}


CShield_Monster::~CShield_Monster()
{
}

void CShield_Monster::Initialize()
{
	m_tInfo.fX = float(WINCX / 2);
	m_tInfo.fY = 1.f;
	m_tInfo.iCX = 160;
	m_tInfo.iCY = 30;
	m_iHp = 85;       //몬스터 최대 체력

	m_fSpeed = 3.f;
	m_iColor[0] = 0; //R
	m_iColor[1] = 255; //G
	m_iColor[2] = 85; //G
}

int CShield_Monster::Update()
{
	if (m_bDead) {
		m_pItem->emplace_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY));
		return OBJ_DEAD;
	}

	int iTime = rand();
	Monster_move(80);
	//float fX = 0.f, fY = 0.f, fDis = 0.f;
	//이동
	/*
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	if (m_tInfo.fY <= m_pTarget->Get_Info().fY + 100 && m_tInfo.fY >= m_pTarget->Get_Info().fY) {}
	else if (m_tInfo.fY >= m_pTarget->Get_Info().fY - 100 && m_tInfo.fY <= m_pTarget->Get_Info().fY) {}
	else if (m_pTarget->Get_Info().fY - 100 < 25)
	{
		fY = m_pTarget->Get_Info().fY-100 - m_tInfo.fY;
	}
	else 
	{
		fY = m_pTarget->Get_Info().fY+100 - m_tInfo.fY;
	}

	fDis = sqrtf(fX * fX + fY * fY);
	if (fDis == 0) { ; }
	else
	{
		m_fAngle = acosf(fX / fDis) * 180.f / PI;
		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;
	}

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	*/

	Update_Rect();
	return OBJ_NOEVENT;
}

void CShield_Monster::Late_Update()
{
	if (0 >= m_iHp) { m_bDead = true; }

	else
	{
		for (int i = m_iColor[2]; i > m_iHp; --i)
		{
			if (m_iColor[0] >= 255)
			{
				m_iColor[1] -= 6;
			}
			else if(m_iColor[0] < 255)
			{
				if (m_iColor[0] + 6 > 255)
				{
					m_iColor[0] += 3;
				}
				else
				{
					m_iColor[0] += 6;
				}
			}
		}
	}
	m_iColor[2] = m_iHp;
	Set_Color(m_iColor[0], m_iColor[1], 0);
}

void CShield_Monster::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield_Monster::Release()
{
}
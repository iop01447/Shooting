#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 150.f;
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_fSpeed = 5.f;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CMonster::Render(HDC _DC)
{
	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}

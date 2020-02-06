#include "stdafx.h"
#include "Trap.h"


CTrap::CTrap()
	: iCheck(0)
{
}


CTrap::~CTrap()
{
}

void CTrap::Initialize()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
	m_fSpeed = 4.f;

	Set_Color(255, 0, 0);
}

int CTrap::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (iCheck != 25)
	{
		float fX = 0.f, fY = 0.f, fDis = 0.f;
		fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
		fDis = sqrtf(fX * fX + fY * fY);

		if (fDis != 0)
		{
			m_fAngle = acosf(fX / fDis) * 180.f / PI;

			if (m_tInfo.fY < m_pTarget->Get_Info().fY)
				m_fAngle *= -1.f;
		}
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
		iCheck++;
	}
	Update_Rect();
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
	{
		m_tInfo.fX -= cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY += sinf(m_fAngle * PI / 180.f) * m_fSpeed;
		Update_Rect();
	}
	

	return OBJ_NOEVENT;
}

void CTrap::Late_Update()
{

}

void CTrap::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTrap::Release()
{
}
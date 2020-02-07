#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f), m_pTarget(nullptr), m_iHp(0), m_iDamage(1)
{
	// 쓰레기값 초기화 방지를 위해 0초기화를 진행한다.
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	m_Brush = CreateSolidBrush(RGB(255, 255, 255));
	m_Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}


CObj::~CObj()
{
	DeleteObject(m_Brush);
	DeleteObject(m_Pen);
}

void CObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CObj::Set_Pos(float _x, float _y)
{
	m_tInfo.fX = _x;
	m_tInfo.fY = _y;
}

HBRUSH CObj::Set_Color(int r, int g, int b)
{
	DeleteObject(m_Brush);
	return m_Brush = CreateSolidBrush(RGB(r, g, b));
}

void CObj::Set_PenColor(int r, int g, int b, int width)
{
	DeleteObject(m_Pen);
	m_Pen = CreatePen(PS_SOLID, width, RGB(r, g, b));
}

void CObj::Set_Pen_UnVisible()
{
	DeleteObject(m_Pen);
	m_Pen = CreatePen(PS_NULL, 1, RGB(0,0,0));
}

void CObj::Monster_move(int iA)
{
	float fX = 0.f, fY = 0.f, fDis = 0.f;

	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	if (m_tInfo.fY <= m_pTarget->Get_Info().fY + iA && m_tInfo.fY >= m_pTarget->Get_Info().fY) {}
	else if (m_tInfo.fY >= m_pTarget->Get_Info().fY - iA && m_tInfo.fY <= m_pTarget->Get_Info().fY) {}
	else if (m_pTarget->Get_Info().fY - iA < 25)
	{
		fY = m_pTarget->Get_Info().fY - iA - m_tInfo.fY;
	}
	else
	{
		fY = m_pTarget->Get_Info().fY + iA - m_tInfo.fY;
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
}

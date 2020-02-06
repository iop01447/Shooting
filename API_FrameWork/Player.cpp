#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


CPlayer::CPlayer()
	:m_iBulletCreateTime(100), m_OldTime(GetTickCount())
{
	ZeroMemory(&m_Points, sizeof(m_Points));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY - 100;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_fDis = 100.f;
	m_fSpeed = 5.f;

	m_fAngle = 90.f;

	Set_Color(255, 0, 0);
	Set_Pen_UnVisible();
}

int CPlayer::Update()
{
	// 이동
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	// 총알 쏘기
	int size = 7;
	BULLET::SHAPE shape = BULLET::SHAPE::CIRCLE;
	if (GetAsyncKeyState(VK_SPACE) && (GetTickCount() - m_OldTime) > m_iBulletCreateTime) {
		m_OldTime = GetTickCount();
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-size, m_tInfo.fY-3*size, shape));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+size, m_tInfo.fY-3*size, shape));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-2*size, m_tInfo.fY, shape));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+2*size, m_tInfo.fY, shape));

	}

	// 스킬
	if (GetAsyncKeyState('Q'))
	{
		Skill_1();
	}

	Update_Rect();
	Update_Polygon();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	Polygon(_DC, m_Points, 4); // 비행기
}

void CPlayer::Release()
{
}

CObj* CPlayer::Create_Bullet()
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);

	return pObj;
}

CObj* CPlayer::Create_Bullet(BULLET::DIR _eDIr)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_eDIr);

	return pObj;
}

CObj * CPlayer::Create_Bullet(float x, float y, BULLET::SHAPE _eShape)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(x, y, m_fAngle);
	dynamic_cast<CBullet*>(pObj)->Set_Shape(_eShape);

	return pObj;
}

void CPlayer::Update_Polygon()
{
	m_Points[0].x = (LONG)m_tInfo.fX - 30;
	m_Points[0].y = (LONG)m_tInfo.fY + 20;
	m_Points[1].x = (LONG)m_tInfo.fX;
	m_Points[1].y = (LONG)m_tInfo.fY - 10;
	m_Points[2].x = (LONG)m_tInfo.fX + 30;
	m_Points[2].y = (LONG)m_tInfo.fY + 20;
	m_Points[3].x = (LONG)m_tInfo.fX;
	m_Points[3].y = (LONG)m_tInfo.fY + 10;
}

void CPlayer::Skill_1()
{
	m_pBullet->emplace_back(Create_Bullet());
}

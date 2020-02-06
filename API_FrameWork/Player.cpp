#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


CPlayer::CPlayer()
{
//	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
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
}

int CPlayer::Update()
{
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

	if (GetAsyncKeyState(VK_SPACE) && (GetTickCount() - m_old_time) > m_create_time) {
		m_old_time = GetTickCount();
		int size = 7;
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-size, m_tInfo.fY-3*size));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+size, m_tInfo.fY-3*size));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-2*size, m_tInfo.fY));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+2*size, m_tInfo.fY));
	}

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
//	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Polygon(_DC, point, 4); // ∫Ò«‡±‚
}

void CPlayer::Release()
{
}

CObj* CPlayer::Create_Bullet()
{
	//CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);

	return pObj;
}

CObj* CPlayer::Create_Bullet(BULLET::DIR _eDIr)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_eDIr);

	return pObj;
}

CObj * CPlayer::Create_Bullet(float x, float y)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(x, y, m_fAngle);

	return pObj;
}

void CPlayer::Update_Polygon()
{
	point[0].x = m_tInfo.fX - 30;
	point[0].y = m_tInfo.fY + 20;
	point[1].x = m_tInfo.fX;
	point[1].y = m_tInfo.fY - 10;
	point[2].x = m_tInfo.fX + 30;
	point[2].y = m_tInfo.fY + 20;
	point[3].x = m_tInfo.fX;
	point[3].y = m_tInfo.fY + 10;
}

void CPlayer::Skill_1()
{
	m_pBullet->emplace_back(Create_Bullet());
}

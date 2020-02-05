#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


CPlayer::CPlayer()
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;


	m_fDis = 100.f;
	m_fSpeed = 5.f;
}

int CPlayer::Update()
{
	if (GetAsyncKeyState(VK_LEFT))
		m_fAngle += 5.f;
	if (GetAsyncKeyState(VK_RIGHT))
		m_fAngle -= 5.f;
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * -m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * -m_fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE))
		m_pBullet->emplace_back(Create_Bullet());


	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	m_tPosin.x = LONG(m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fDis);
	m_tPosin.y = LONG(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fDis);
}

void CPlayer::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_DC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_DC, (int)m_tPosin.x, (int)m_tPosin.y);
}

void CPlayer::Release()
{
}

CObj* CPlayer::Create_Bullet()
{
	CObj* pObj = CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);

	return pObj;
}

CObj* CPlayer::Create_Bullet(BULLET::DIR _eDIr)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_eDIr);

	return pObj;
}

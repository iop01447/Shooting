#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "RotationBullet.h"


CPlayer::CPlayer()
	:m_iBulletCreateTime(100), m_BulletOldTime(GetTickCount()), m_GazeMaxTime(5000), m_OldGazeTime(GetTickCount()), m_iSkillCnt(5), m_bUnDead(false)
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
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 15;

	m_fDis = 100.f;
	m_fSpeed = 5.f;

	m_fAngle = 90.f;

	Set_Color(55, 52, 235);
	Set_Pen_UnVisible();

	m_StarPos[0] = { 101, 0 };
	m_StarPos[1] = { 77, 77 };
	m_StarPos[2] = { 0, 77 };
	m_StarPos[3] = { 62, 125 };
	m_StarPos[4] = { 39, 201 };
	m_StarPos[5] = { 101, 153 };
	m_StarPos[6] = { 163, 201 };
	m_StarPos[7] = { 138, 125 };
	m_StarPos[8] = { 201, 77 };
	m_StarPos[9] = { 124, 77 };
	m_StarPos[10] = { 101, 0 };
	for (int i = 0; i < 11; ++i) {
		m_StarPos[i].x *= 0.1;
		m_StarPos[i].y *= 0.1;
	}

	m_iHp = 5;
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_iHp < 1) {
		if (m_bUnDead)
			m_iHp = 1;
		else {
			m_iHp = 0;
			m_bDead = true;
		}
	}

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
	if (GetAsyncKeyState(VK_SPACE) && Can_Shoot_Bullet(m_iBulletCreateTime)) {
		m_BulletOldTime = GetTickCount();
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-size, m_tInfo.fY-3*size-10));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+size, m_tInfo.fY-3*size-10));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX-2*size, m_tInfo.fY-10));
		m_pBullet->emplace_back(Create_Bullet(m_tInfo.fX+2*size, m_tInfo.fY-10));
	}

	// 스킬 카운트 증가
	if ((GetTickCount() - m_OldGazeTime) > m_GazeMaxTime) {
		m_OldGazeTime = GetTickCount();
		++m_iSkillCnt;
		if (m_iSkillCnt > 5)
			m_iSkillCnt = 5;
	}

	// 스킬
	if (GetAsyncKeyState('Q') && m_iSkillCnt && Can_Shoot_Bullet(200))
	{
		m_OldGazeTime = GetTickCount();
		--m_iSkillCnt;
		if (m_iSkillCnt < 0)
			m_iSkillCnt = 0;

		m_BulletOldTime = GetTickCount();
		Skill_1();
	}

	// 무적모드 설정
	if (GetAsyncKeyState('U'))
	{
		m_bUnDead = true;
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
	// 비행기
	SelectObject(_DC, Set_Color(55, 52, 235));
	Polygon(_DC, m_Points, 4); 
	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// 목숨
	SelectObject(_DC, Set_Color(255, 0, 0));
	for (int i = 0; i < m_iHp; ++i) {
		Draw_Star(_DC, 50 + i*25, 45);
	}

	// 스킬 카운트
	SelectObject(_DC, Set_Color(122, 52, 235));
	int x = 0, y = 0, size = 0;
	for (int i = 0; i < m_iSkillCnt; ++i) {
		x = 60 + i * 25;
		y = WINCY - 50;
		size = 10;
		Ellipse(_DC, x - size, y - size, x + size, y + size);
	}
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

CObj * CPlayer::Create_Bullet(float x, float y)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(x, y, m_fAngle);
	dynamic_cast<CBullet*>(pObj)->Set_Shape(BULLET::SHAPE::ELLIPSE);
	pObj->Set_Color(52, 137, 235);
	pObj->Set_Pen_UnVisible();

	return pObj;
}

CObj * CPlayer::Create_Bullet(float x, float y, float angle, BULLET::SHAPE shape)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(x, y, angle);
	dynamic_cast<CBullet*>(pObj)->Set_Shape(shape);
	pObj->Set_Color(52, 137, 235);
	pObj->Set_Pen_UnVisible();

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

void CPlayer::Draw_Star(HDC _DC, int _x, int _y)
{
	POINT pos[11];
	for (int i = 0; i < 11; ++i) {
		pos[i].x = m_StarPos[i].x + _x;
		pos[i].y = m_StarPos[i].y + _y;
	}

	Polygon(_DC, pos, 11);
}

void CPlayer::Skill_1()
{
	int cnt = 20;
	float angle = 0;
	bool reverse = false;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < cnt; ++i) {
			angle = i * (360.f / cnt);
			CObj *pObj = Create_Bullet<CRotationBullet>(m_tInfo.fX, m_tInfo.fY, angle);
			dynamic_cast<CRotationBullet*>(pObj)->Set_RotSpeed(reverse);
			dynamic_cast<CRotationBullet*>(pObj)->Set_RotDis(j * 50);
			m_pBullet->emplace_back(pObj);
		}
		reverse = !reverse;
	}
}

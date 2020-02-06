#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "Boss.h"
#include "MiniGun.h"
#include "Kamikaze.h"
#include "Focus_Monster.h"
#include "Bounce_Monster.h"
#include "Shotgun_Monster.h"
#include "Shield_Monster.h"
#include "Trap_Monster.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_dwTime(GetTickCount()), m_iFPS(0), m_szFPS(L""), m_iStage(0), iTime(0)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	RECT crt;
	GetClientRect(g_hWnd, &crt);
	m_DC = GetDC(g_hWnd);
	m_BackBufferDC = CreateCompatibleDC(m_DC);
	m_hBit = CreateCompatibleBitmap(m_DC, crt.right, crt.bottom);
	m_OldBit = (HBITMAP)SelectObject(m_BackBufferDC, m_hBit);
	FillRect(m_BackBufferDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	m_listObj[OBJID::PLAYER].emplace_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_listObj[OBJID::PLAYER].front())->Set_Bullet(&m_listObj[OBJID::PLAYER_BULLET]);

	//m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
	//m_listObj[OBJID::MONSTER].front()->Set_Target(m_listObj[OBJID::PLAYER].front());
	//dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);

	m_listObj[OBJID::MOUSE].emplace_back(CAbstractFactory<CMouse>::Create());	
}

void CMainGame::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto& iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}

	////////////////스테이지////////////몬스터 생성
	if (m_listObj[OBJID::MONSTER].empty() && m_listObj[OBJID::BOSS].empty())
	{
		switch (m_iStage)
		{
		case 0:
			Spwan_Kamikaze_Monster(float(WINCX - 100), 0.f);
			Spwan_Kamikaze_Monster(float(100), 0.f);

			Spwan_Normal_Monster(float(WINCX / 2), 0.f);
			Spwan_Normal_Monster(float(WINCX - 100), 0.f);
			Spwan_Normal_Monster(float(100), 0.f);
			break;
		case 1:
			Spwan_Focus_Monster(float(WINCX / 2), 0.f);
			Spwan_Focus_Monster(float(WINCX - 100), 0.f);
			Spwan_Focus_Monster(float(100), 0.f);

			Spwan_Shield_Monster(float(WINCX / 2), 25.f);
			Spwan_Shield_Monster(float(WINCX - 100), 25.f);
			Spwan_Bounce_Monster(float(WINCX - 100), 0.f);
			Spwan_Shield_Monster(float(100), 0.f);
			break;
		case 2:
			Spwan_Bounce_Monster(float(WINCX - 100), 0.f);
			Spwan_Shield_Monster(float(WINCX - 100), 0.f);
			Spwan_Bounce_Monster(float(100), 0.f);
			Spwan_Shield_Monster(float(100), 0.f);
			Spwan_Focus_Monster(float(WINCX / 4 *1), 0.f);
			Spwan_Focus_Monster(float(WINCX - 100), 0.f);
			Spwan_Focus_Monster(float(WINCX /4*3), 0.f);
			Spwan_Focus_Monster(float(100), 0.f);
			break;
		case 3:
			Spwan_Trap_Monster(float(100), 0.f);
			break;
		case 4:
			Generate_Boss();
			return;
		case 5:
			return;
		}
		++m_iStage;
	}
}


void CMainGame::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Late_Update();
	}

	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BULLET]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::PLAYER_BULLET]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MONSTER]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::BOSS], m_listObj[OBJID::PLAYER_BULLET]);	
}

void CMainGame::Render()
{
	m_OldBit = (HBITMAP)SelectObject(m_BackBufferDC, m_hBit);

	Rectangle(m_BackBufferDC, 0, 0, WINCX, WINCY);
	Rectangle(m_BackBufferDC, 25, 25, WINCX - 25, WINCY - 25);

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i]) {
			SelectObject(m_BackBufferDC, pObj->Get_Brush());
			SelectObject(m_BackBufferDC, pObj->Get_Pen());
			pObj->Render(m_BackBufferDC);
		}
	}

	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	BitBlt(m_DC, 0, 0, WINCX, WINCY, m_BackBufferDC, 0, 0, SRCCOPY);
	SelectObject(m_BackBufferDC, m_OldBit);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_DC);
	ReleaseDC(g_hWnd, m_BackBufferDC);

	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

void CMainGame::Generate_Boss()
{
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CBoss>::Create());
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Boss(&m_listObj[OBJID::BOSS]);
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX / 2 + MINIGUN_DIS, 200.f));
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Right(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Id(MINIGUN::RIGHT);
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX / 2 - MINIGUN_DIS, 200.f));
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Left(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Id(MINIGUN::LEFT);
}

void CMainGame::Spwan_Normal_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
}

void CMainGame::Spwan_Kamikaze_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CKamikaze>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
}

void CMainGame::Spwan_Focus_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CFocus_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CFocus_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
}

void CMainGame::Spwan_Bounce_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CBounce_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CBounce_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
}

void CMainGame::Spwan_Shotgun_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CShotgun_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CShotgun_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
}

void CMainGame::Spwan_Shield_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CShield_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CShield_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
}

void CMainGame::Spwan_Trap_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CTrap_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CTrap_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
}

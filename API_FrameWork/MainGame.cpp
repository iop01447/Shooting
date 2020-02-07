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
	: m_pPlayer(nullptr), m_dwTime(GetTickCount()), m_iFPS(0), m_szFPS(L""), m_iStage(0), iTime(0), m_eState(MAINGAME::END), m_ePrev(MAINGAME::END)
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

	m_Screen = CreateSolidBrush(RGB(0, 0, 0));

	SetTextAlign(m_BackBufferDC, TA_CENTER);
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
	if (m_listObj[OBJID::PLAYER].empty())
	{
		m_eState = MAINGAME::GAMEOVER;
		if (m_eState != m_ePrev)
			iTime = 0;
		m_ePrev = m_eState;

		/*m_Font=CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"궁서");
		m_Old_Font = (HFONT)SelectObject(m_DC, m_Font);
		TCHAR str[] = L"Game Over!";
		TextOut(m_DC, 100, 200, str, lstrlen(str));
		SelectObject(m_DC, m_Old_Font);
		DeleteObject(m_Font);*/

	}
		
	////////////////스테이지////////////몬스터 생성
	if (m_listObj[OBJID::MONSTER].empty() && m_listObj[OBJID::BOSS].empty())
	{
		switch (m_iStage)
		{
		case 0:
			Spwan_Kamikaze_Monster(float(WINCX - 100), 0.f);
			Spwan_Kamikaze_Monster(float(100), 0.f);

			Spwan_Shotgun_Monster(float(WINCX / 2), 0.f);
			Spwan_Shotgun_Monster(float(WINCX), 0.f);
			Spwan_Shotgun_Monster(float(0), 0.f);
			break;
		case 1:
			Spwan_Focus_Monster(float(WINCX / 2), 0.f);
			Spwan_Focus_Monster(float(WINCX - 100), 0.f);
			Spwan_Focus_Monster(float(100), 0.f);

			Spwan_Shotgun_Monster(float(WINCX / 2), 0.f);
			Spwan_Shotgun_Monster(float(WINCX), 0.f);
			Spwan_Shotgun_Monster(float(0), 0.f);

			break;
		case 2:
			Spwan_Bounce_Monster(float(WINCX - 100), 0.f);
			Spwan_Bounce_Monster(float(100), 0.f);

			Spwan_Shield_Monster(float(WINCX / 2), 45.f);
			Spwan_Shield_Monster(float(WINCX - 100), 45.f);
			Spwan_Shield_Monster(float(100), 45.f);

			Spwan_Focus_Monster(float(WINCX / 4 *1+100), 0.f);
			Spwan_Focus_Monster(float(WINCX - 100), 0.f);
			Spwan_Focus_Monster(float(WINCX /4*3-100), 0.f);
			Spwan_Focus_Monster(float(100), 0.f);
			break;
		case 3:
			Spwan_Shotgun_Monster(float(WINCX / 2), 0.f);
			Spwan_Shotgun_Monster(float(WINCX), 0.f);
			Spwan_Shotgun_Monster(float(0), 0.f);

			Spwan_Normal_Monster(float(WINCX / 2), 20.f);
			Spwan_Normal_Monster(float(WINCX), 20.f);
			Spwan_Normal_Monster(float(0), 20.f);

			Spwan_Shield_Monster(float(WINCX / 2), 45.f);
			Spwan_Shield_Monster(float(WINCX - 100), 45.f);
			Spwan_Shield_Monster(float(100), 45.f);
			break;
		case 4:
			Spwan_Trap_Monster(float(0), 0.f);
			Spwan_Trap_Monster(float(WINCX), 0.f);
			Spwan_Trap_Monster(float(WINCX / 2), 0.f);

			Spwan_Normal_Monster(float(WINCX / 2), 20.f);
			Spwan_Normal_Monster(float(WINCX), 20.f);
			Spwan_Normal_Monster(float(0), 20.f);

			Spwan_Kamikaze_Monster(float(WINCX - 100), 20.f);
			Spwan_Kamikaze_Monster(float(100), 20.f);

			Spwan_Shield_Monster(float(WINCX / 2), 35.f);
			Spwan_Shield_Monster(float(WINCX - 100), 35.f);
			Spwan_Shield_Monster(float(100), 35.f);

			Spwan_Focus_Monster(float(WINCX / 2), 10.f);
			Spwan_Focus_Monster(float(WINCX - 100), 10.f);
			Spwan_Focus_Monster(float(100), 10.f);

			Spwan_Shotgun_Monster(float(WINCX / 2), 0.f);
			Spwan_Shotgun_Monster(float(WINCX), 0.f);
			Spwan_Shotgun_Monster(float(0), 0.f);
			break;
		case 5:
			Generate_Boss();
			break;
		case 6:
			m_eState = MAINGAME::COMPLETE;
			iTime = 0;
			break;
		}
		++m_iStage;
	}
	++iTime;
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
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::ITEM], OBJID::PLAYER, OBJID::ITEM);
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
	
	//게임오버
	if (m_eState == MAINGAME::GAMEOVER)
	{
		m_Font = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"궁서");
		m_Old_Font = (HFONT)SelectObject(m_BackBufferDC, m_Font);
		TCHAR str[] = L"Game Over!";
		RECT Screen = {};
		Screen.top = 800 - 5 * iTime;
		Screen.left = 0;
		Screen.right = WINCX;
		Screen.bottom = WINCY;
		FillRect(m_BackBufferDC, &Screen, m_Screen);
		SetTextAlign(m_DC, TA_CENTER);
		if(iTime>=160)
			TextOut(m_BackBufferDC, 300, 200, str, lstrlen(str));
		else
			TextOut(m_BackBufferDC, 300, 1000-5*iTime, str, lstrlen(str));
		SelectObject(m_BackBufferDC, m_Old_Font);
		DeleteObject(m_Font);
		
	}
	//게임 클리어
	if (m_eState == MAINGAME::COMPLETE)
	{
		m_Font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"궁서");
		m_Old_Font = (HFONT)SelectObject(m_BackBufferDC, m_Font);
		TCHAR str[] = L"Game_Complete!";
		/*RECT Screen = {};
		Screen.top = 800 - 5 * iTime;
		Screen.left = 0;
		Screen.right = WINCX;
		Screen.bottom = WINCY;
		FillRect(m_BackBufferDC, &Screen, m_Screen);*/
		SetTextAlign(m_DC, TA_CENTER);
		if (iTime >= 120)
			TextOut(m_BackBufferDC, 300, 200, str, lstrlen(str));
		else
			TextOut(m_BackBufferDC, 300, 800 - 5 * iTime, str, lstrlen(str));
		SelectObject(m_BackBufferDC, m_Old_Font);
		DeleteObject(m_Font);

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
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Target(m_listObj[OBJID::PLAYER].front());
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX / 2 - MINIGUN_DIS, 200.f));
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Left(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Id(MINIGUN::LEFT);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Target(m_listObj[OBJID::PLAYER].front());
}

void CMainGame::Spwan_Normal_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Item(&m_listObj[OBJID::ITEM]); // 추가
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
	dynamic_cast<CFocus_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Item(&m_listObj[OBJID::ITEM]); // 추가
}

void CMainGame::Spwan_Bounce_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CBounce_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CBounce_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CBounce_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Item(&m_listObj[OBJID::ITEM]); // 추가
}

void CMainGame::Spwan_Shotgun_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CShotgun_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CShotgun_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CShotgun_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Item(&m_listObj[OBJID::ITEM]); // 추가
}

void CMainGame::Spwan_Shield_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CShield_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CShield_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Item(&m_listObj[OBJID::ITEM]); // 추가
}

void CMainGame::Spwan_Trap_Monster(float _fX, float _fY)
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CTrap_Monster>::Create(_fX, _fY));
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CTrap_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CTrap_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Item(&m_listObj[OBJID::ITEM]);
}

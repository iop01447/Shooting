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


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_dwTime(GetTickCount()), m_iFPS(0), m_szFPS(L""), m_iStage(0), m_MonsterMax(1), iTime(0)
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

	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
	m_listObj[OBJID::MONSTER].front()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);

	m_listObj[OBJID::MOUSE].emplace_back(CAbstractFactory<CMouse>::Create());


	/*
	//보스생성코드 시작 -> 싫으면 주석처리
	/*m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CBoss>::Create());	
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Boss(&m_listObj[OBJID::BOSS]);
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX/2+MINIGUN_DIS, 200.f)); 
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Right(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Id(MINIGUN::RIGHT);
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX / 2 - MINIGUN_DIS, 200.f));
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Left(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Id(MINIGUN::LEFT);*/
	//보스생성코드 끝 
	*/
	
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

		if (iTime >= 190 && iTime % 190 == 0)
		{
			m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CFocus_Monster>::Create());
			m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
			dynamic_cast<CFocus_Monster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);

			m_MonsterMax++;
		}
		//30초에 하나 생성
		if (iTime >= 1950 && iTime % 1950 == 0)
		{
			m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CKamikaze>::Create());
			m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
			m_MonsterMax++;
		}

		// 10초에 하나 생성
		else if (iTime >= 650 && iTime % 650 == 0)
		{
			m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
			m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
			dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
		}

		iTime++;
	/*
	/////////////////////잡몹 랜덤 생성 ++한도 10마리
	int iTime = rand();
	if (m_MonsterMax < 10)
	{
		if (iTime % 100 == 0)
		{
			m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CKamikaze>::Create());
			m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
			m_MonsterMax++;
		}
		else if (iTime % 50 == 0)
		{
			m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
			m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
			dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
			m_MonsterMax++;

		}
	///////////////////////잡몹 랜덤 생성
	//int iTime = rand();
	//if (iTime % 500 == 0)
	//{
	//	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
	//	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	//	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Id(OBJID::MONSTER);
	//	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	//}
	////////////////////////

	if (m_listObj[OBJID::MONSTER].empty() && m_listObj[OBJID::BOSS].empty())
	{
		switch (m_iStage)
		{
		case 0:
			Generate_Monster_0();
			break;
		case 1:
			Generate_Monster_0();
			break;
		case 2:
			Generate_Monster_0();
			break;
		case 3:
			Generate_Boss();
			break;
		case 4:
			//게임 종료
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

	//CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BULLET]);
	//CCollisionMgr::Collision_Sphere(m_listObj[OBJID::MOUSE], m_listObj[OBJID::BULLET]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::BULLET]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::PLAYER_BULLET]);
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

	//TCHAR szBuff[32] = L"";
	//wsprintf(szBuff, L"Bullet: %d", m_listObj[OBJID::BULLET].size());
	//TextOut(m_BackBufferDC, 50, 50, szBuff, lstrlen(szBuff));


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
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Target(m_listObj[OBJID::PLAYER].front());
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX / 2 - MINIGUN_DIS, 200.f));
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Left(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Id(MINIGUN::LEFT);
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Target(m_listObj[OBJID::PLAYER].front());
}

void CMainGame::Generate_Monster_0()
{
	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
	m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Id(OBJID::MONSTER);
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
}

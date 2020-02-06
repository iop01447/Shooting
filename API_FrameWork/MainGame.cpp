#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "Boss.h"
#include "MiniGun.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_dwTime(GetTickCount()), m_iFPS(0), m_szFPS(L"")
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	m_listObj[OBJID::PLAYER].emplace_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_listObj[OBJID::PLAYER].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);

	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
	m_listObj[OBJID::MONSTER].front()->Set_Target(m_listObj[OBJID::PLAYER].front());
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].front())->Set_Id(OBJID::MONSTER);
	dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);

	m_listObj[OBJID::MOUSE].emplace_back(CAbstractFactory<CMouse>::Create());


	//보스생성코드 시작 -> 싫으면 주석처리
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CBoss>::Create());	
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Boss(&m_listObj[OBJID::BOSS]);
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX/2+MINIGUN_DIS, 200.f)); 
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Right(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	m_listObj[OBJID::BOSS].emplace_back(CAbstractFactory<CMiniGun>::Create(WINCX / 2 - MINIGUN_DIS, 200.f));
	dynamic_cast<CBoss*>(m_listObj[OBJID::BOSS].front())->Set_Left(m_listObj[OBJID::BOSS].back());
	dynamic_cast<CMiniGun*>(m_listObj[OBJID::BOSS].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	//보스생성코드 끝 

	
}

void CMainGame::Update()
{
	float fX, fY;
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

	/////////////////////잡몹 랜덤 생성
	int iTime = rand();
	if (iTime % 500 == 0)
	{
		m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create());
		m_listObj[OBJID::MONSTER].back()->Set_Target(m_listObj[OBJID::PLAYER].front());
		dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Id(OBJID::MONSTER);
		dynamic_cast<CMonster*>(m_listObj[OBJID::MONSTER].back())->Set_Bullet(&m_listObj[OBJID::BULLET]);
	}
	////////////////////////
}


void CMainGame::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Late_Update();
	}

	//CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BULLET]);
	CCollisionMgr::Collision_Sphere(m_listObj[OBJID::MOUSE], m_listObj[OBJID::BULLET]);
}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	Rectangle(m_DC, 25, 25, WINCX - 25, WINCY - 25);

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render(m_DC);
	}

	TCHAR szBuff[32] = L"";
	wsprintf(szBuff, L"Bullet: %d", m_listObj[OBJID::BULLET].size());
	TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));


	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_DC);

	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

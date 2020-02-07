#include "stdafx.h"
#include "Item.h"


CItem::CItem()
	:m_eId(ITEM::ID::END)
{
}


CItem::~CItem()
{
}

void CItem::Initialize()
{
	m_tInfo.iCY = 20;
	m_fSpeed = 1 + rand()%3;

	if (rand() % 10 < 5) { // 50%의 확률로 아이템 드랍 안됨 -> 몬스터에서 해줘야 함... 그냥 여기서 하겠다
		m_bDead = true;
		return;
	}
	int randint = rand() % 100;
	if (randint < 20) {
		m_eId = ITEM::ID::SKILL_UP;
		m_tInfo.iCX = 70;
	}
	else if (randint < 40) {
		m_eId = ITEM::ID::SKILL;
		m_tInfo.iCX = 40;
	}
	else {
		m_eId = ITEM::ID::HP;
		m_tInfo.iCX = 25;
	}
}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;
	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CItem::Render(HDC _DC)
{
	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	TCHAR szBuff[32] = L"";

	SetTextColor(_DC, RGB(255, 255, 255));
	switch (m_eId)
	{
	case ITEM::ID::HP:
		SetBkColor(_DC, RGB(255, 0, 0)); // 배경 색상
		wsprintf(szBuff, L"HP");
		break;
	case ITEM::ID::SKILL_UP:
		SetBkColor(_DC, RGB(55, 52, 235));
		wsprintf(szBuff, L"SKILL_UP");
		break;
	case ITEM::ID::SKILL:
		SetBkColor(_DC, RGB(122, 52, 235));
		wsprintf(szBuff, L"SKILL");
		break;
	}

	TextOut(_DC, m_tInfo.fX, m_tInfo.fY-8, szBuff, lstrlen(szBuff));

	// 원상 복귀
	SetTextColor(_DC, RGB(0, 0, 0));
	SetBkColor(_DC, RGB(255, 255, 255));
}

void CItem::Release()
{
}

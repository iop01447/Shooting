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
	m_tInfo.iCX = 25;
	m_tInfo.iCY = 20;

	//if (rand() % 10) return; // 10%의 확률로 아이템 드랍 안됨 -> 몬스터에서 해줘야 함...
	if (rand() % 100 < 80) // 80%의 확률
		m_eId = ITEM::ID::HP;
	else
		m_eId = ITEM::ID::SKILL_UP;
}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
}

void CItem::Render(HDC _DC)
{
	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	TCHAR szBuff[32] = L"";
	SetTextAlign(_DC, TA_CENTER);

	switch (m_eId)
	{
	case ITEM::ID::HP:
		wsprintf(szBuff, L"HP");
		break;
	case ITEM::ID::SKILL_UP:
		wsprintf(szBuff, L"SKILL_UP");
		break;
	}

	TextOut(_DC, m_tInfo.fX, m_tInfo.fY-8, szBuff, lstrlen(szBuff));
}

void CItem::Release()
{
}

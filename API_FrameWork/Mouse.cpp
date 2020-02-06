#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;
}

int CMouse::Update()
{
	// GetCursorPos() : ���콺 Ŀ���� ��ġ ��ǥ�� ������ �Լ�
	// ScreenToClient() : ��ü ��ũ�� �������� Ŭ���̾�Ʈ ��ǥ�� ��ȯ���ش�!
	// ShowCursor() : ���콺�� �׸��� ���� �������ִ� �Լ�
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	//ShowCursor(FALSE);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
}

void CMouse::Render(HDC _DC)
{
	//Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}

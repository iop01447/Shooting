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
	// GetCursorPos() : 마우스 커서의 위치 좌표를 얻어오는 함수
	// ScreenToClient() : 전체 스크린 영역에서 클라이언트 좌표로 변환해준다!
	// ShowCursor() : 마우스를 그릴지 말지 결정해주는 함수
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

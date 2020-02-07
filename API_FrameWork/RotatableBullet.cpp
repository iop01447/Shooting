#include "stdafx.h"
#include "RotatableBullet.h"


CRotatableBullet::CRotatableBullet()
{
}


CRotatableBullet::~CRotatableBullet()
{
}

void CRotatableBullet::Initialize()
{
	m_tInfo.iCX = 15;
	m_tInfo.iCY = 15;

	m_fSpeed = 7.f;
	m_iDamage = 1;

	m_tShape[0] = { 7, 0 };
	m_tShape[1] = { -7, 4 };
	m_tShape[2] = { -22, 4 };
	m_tShape[3] = { -37, 0 };
	m_tShape[4] = { -22, -4 };
	m_tShape[5] = { -7, -4 };
}

int CRotatableBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//m_tInfo.fY -= m_fSpeed;
	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CRotatableBullet::Late_Update()
{
	if (25 >= m_tRect.top || 25 >= m_tRect.left
		|| WINCX - 25 <= m_tRect.right || WINCY - 25 <= m_tRect.bottom)
		m_bDead = true;
}

void CRotatableBullet::Render(HDC _DC)
{
	POINT tShape[POINTARR_SIZE] = {};
	Rotate(tShape, m_tShape, POINTARR_SIZE, m_fAngle);
	Add_Cord(tShape, POINTARR_SIZE);
	Polygon(_DC, tShape, POINTARR_SIZE);
}

void CRotatableBullet::Release()
{
}

void CRotatableBullet::Rotate(POINT* _ppDst, POINT* _pShape, int _iSize, float _fAngle)
{
	for (int i = 0; i < _iSize; i++)
	{
		(_ppDst)[i].x = cosf(_fAngle*PI / 180.f)*_pShape[i].x - sinf(_fAngle*PI / 180.f)*_pShape[i].y;
		(_ppDst)[i].y =- sinf(_fAngle*PI / 180.f)*_pShape[i].x - cosf(_fAngle*PI / 180.f)*_pShape[i].y;
	}
}

void CRotatableBullet::Add_Cord(POINT * _pDst, int _iSize)
{
	for (int i = 0; i < _iSize; ++i)
	{
		_pDst[i].x += m_tInfo.fX;
		_pDst[i].y += m_tInfo.fY;
	}
}

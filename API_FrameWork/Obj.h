#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	// 상태 판단 용 함수
	// Update보다 늦게 진행되어 이동 후 결과를 판단하기 위해 사용한다.
	virtual void Late_Update() = 0;		
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

protected:
	void Update_Rect();

public:
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }

public:
	virtual void Set_Dead() { m_bDead = true; }
	void Set_Pos(float _x, float _y);
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	HBRUSH Set_Color(int r, int g, int b);
	void Set_PenColor(int r, int g, int b, int width = 1);
	void Set_Pen_UnVisible();

	HBRUSH Get_Brush() { return m_Brush; }
	HPEN Get_Pen() { return m_Pen; }

protected:
	INFO	m_tInfo;		// 객체들의 좌표와 크기를 저장한다.
	RECT	m_tRect;		// 저장된 좌표와 크기를 통해 Rect를 만든다.

	float	m_fSpeed;
	bool	m_bDead;

	float	m_fAngle;

	HBRUSH	m_Brush;
	HPEN	m_Pen;
};

#endif // !__OBJ_H__
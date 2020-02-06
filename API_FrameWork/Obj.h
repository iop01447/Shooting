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
	void Set_Dead() { m_bDead = true; }
	void Set_Pos(float _x, float _y);
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Add_Angle(float _fAngle) { m_fAngle += _fAngle; }
	void Damage_Hp(int _iDamage) { m_iHp -= _iDamage; }
	void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void Set_AngleSpeed(float _fAngleSpeed) { m_fAngleSpeed = _fAngleSpeed; }
	float Get_Angle() { return m_fAngle; }

protected:
	INFO	m_tInfo;		// 객체들의 좌표와 크기를 저장한다.
	RECT	m_tRect;		// 저장된 좌표와 크기를 통해 Rect를 만든다.

	float	m_fSpeed;
	bool	m_bDead;

	float	m_fAngle;
	float	m_fAngleSpeed;

	int		m_iHp;
};

#endif // !__OBJ_H__
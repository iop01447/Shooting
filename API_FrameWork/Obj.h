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
	bool Is_Dead() { return m_bDead; }

	void Set_Dead() { m_bDead = true; }
	void Set_Pos(float _x, float _y);
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void Set_AngleSpeed(float _fAngleSpeed) { m_fAngleSpeed = _fAngleSpeed; }
	void Set_Damage(int _iDamage) { m_iDamage = _iDamage; }
	
	int Get_Damage() { return m_iDamage; }
	float Get_Angle() { return m_fAngle; }
	
	void Add_Angle(float _fAngle) { m_fAngle += _fAngle; }
	void Damage_Hp(int _iDamage) { m_iHp -= _iDamage; }
	
public:
	HBRUSH Set_Color(int r, int g, int b);
	void Set_PenColor(int r, int g, int b, int width = 1);
	void Set_Pen_UnVisible();

	HBRUSH Get_Brush() { return m_Brush; }
	HPEN Get_Pen() { return m_Pen; }

public:
	void Monster_move(int iA);

public:
	virtual void Collision(CObj* _obj, OBJID::ID _id) {}

protected:
	INFO	m_tInfo;		// 객체들의 좌표와 크기를 저장한다.
	RECT	m_tRect;		// 저장된 좌표와 크기를 통해 Rect를 만든다.
	CObj*	m_pTarget;

	float	m_fSpeed;
	bool	m_bDead;

	float	m_fAngle;

	HBRUSH	m_Brush;
	HPEN	m_Pen;
	float	m_fAngleSpeed;

	int		m_iHp;
	int		m_iDamage;
};

#endif // !__OBJ_H__
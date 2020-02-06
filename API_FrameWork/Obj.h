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
	// ���� �Ǵ� �� �Լ�
	// Update���� �ʰ� ����Ǿ� �̵� �� ����� �Ǵ��ϱ� ���� ����Ѵ�.
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
	INFO	m_tInfo;		// ��ü���� ��ǥ�� ũ�⸦ �����Ѵ�.
	RECT	m_tRect;		// ����� ��ǥ�� ũ�⸦ ���� Rect�� �����.

	float	m_fSpeed;
	bool	m_bDead;

	float	m_fAngle;
	float	m_fAngleSpeed;

	int		m_iHp;
};

#endif // !__OBJ_H__
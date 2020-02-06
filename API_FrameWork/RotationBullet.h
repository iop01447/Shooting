#pragma once
#include "Obj.h"
class CRotationBullet :
	public CObj
{
public:
	CRotationBullet();
	virtual ~CRotationBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_RotSpeed(bool reverse) { if(reverse) m_fRotSpeed *= -1; }
	void Set_RotDis(float add) { m_fRotDis += add; }

private:
	POINT		m_tCenter;
	float		m_fRotAngle;
	float		m_fRotSpeed;
	float		m_fRotDis;

	bool		m_bStart;
};


#include "stdafx.h"
#include "Monster.h"
#include "Bullet.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 150.f;
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;

	m_fSpeed = 3.f;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	int iTime = rand(), iX;

	float fX = 0.f, fY = 0.f, fDis = 0.f;
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;


	//////////////총알발사 --> 하드코딩 수정필요
	if (m_tInfo.fX >= m_pTarget->Get_Info().fX)
	{
		iX = 1;
	}
	else
	{
		iX = 0;
	}

	if (m_tInfo.fY >= m_pTarget->Get_Info().fY)
	{
		if (iTime % 1500 == 0)
		{
			Bullet_Aoe();
		}
		else if (iTime % 150 == 0 && iX == 1)
		{
			m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICLU));
		}
		else if (iTime % 150 == 0)
		{
			m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICRU));

		}
	}
	else
	{
		if (iTime % 1500 == 0)
		{
			Bullet_Aoe();
		}
		else if (iTime % 150 == 0 && iX == 1)
		{
			m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICLD));
		}
		else if (iTime % 150 == 0)
		{
			m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICRD));
		}
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}


CObj* CMonster::Create_Bullet(BULLET::DIR _eDIr)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, m_fAngle);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_eDIr);

	return pObj;
}

CObj * CMonster::Create_Bullet(BULLET::DIR _eDIr, float _fAngle)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, _fAngle);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_eDIr);
	return pObj;
}

void CMonster::Bullet_Aoe() //8방향 발사
{
	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::UP));
	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::DOWN));
	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::RIGHT));
	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::LEFT));

	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICRD, 45.f));
	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICLD, 45.f));
	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICRU, 45.f));
	m_pMonsterBullet->emplace_back(Create_Bullet(BULLET::MONSTER_BASICLU, 45.f));


}

//////////두번째 잡몹 - 자폭병 이동코드(공격능력삭제)
int CMonster::KamiKaze()
{
	float fX = 0.f, fY = 0.f, fDis = 0.f;
	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	fDis = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDis) * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}
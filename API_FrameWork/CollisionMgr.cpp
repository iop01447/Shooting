#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src) //앞에 플레이어 or 몬스터 뒤에 불렛
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Damage_Hp(Src->Get_Damage());
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src, OBJID::ID _DstId, OBJID::ID _SrcId)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Collision(Src, _SrcId);
				Src->Collision(Src, _DstId);
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	// abs() : 절대값을 구해준다!
	// sqrtf() : 
	float	fX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float	fY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);
	float	fDistance = sqrtf(fX * fX + fY * fY);

	float	fRadius = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iCX) >> 1);
	//float	fRadius = (_Dst->Get_Info().iCX + _Src->Get_Info().iCX) * 0.5f;
	//float	fRadius = (_Dst->Get_Info().iCX + _Src->Get_Info().iCX) / 2.f;

	return fRadius > fDistance;
}

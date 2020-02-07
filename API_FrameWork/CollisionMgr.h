#pragma once

#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__



class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// ��ü�� �������� �ʰ� ������ �����ڸ� ���� ȣ���� �����ϴ�!
	// ���ڷ� list�� �޴� ������ �浹 ��ü�� �ϳ���� Ȯ���� �� ����!
	// -> �� �� �� �浹 ó���� �˻��ϱ� ���� list�� �Ѱ��ش�.
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src, OBJID::ID _DstId, OBJID::ID _SrcId);
//	void Collision_Shield_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);
	static bool Check_Sphere(CObj* _Dst, CObj* _Src);
};


#endif // !__COLLISIONMGR_H__

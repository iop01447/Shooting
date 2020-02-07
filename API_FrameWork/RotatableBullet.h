#pragma once
#include "Obj.h"

#define POINTARR_SIZE 6

class CRotatableBullet :
	public CObj
{
public:
	CRotatableBullet();
	virtual ~CRotatableBullet();

	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();

	void Rotate(POINT* _ppDst,POINT* _pShape, int _iSize, float _fAngle);
	void Add_Cord(POINT* _pDst, int _iSize);

private:
	POINT m_tShape[POINTARR_SIZE];

};


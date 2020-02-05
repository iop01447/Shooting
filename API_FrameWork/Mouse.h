#pragma once

#ifndef __MOUSE_H__
#define __MOUSE_H__


#include "Obj.h"
class CMouse : public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);
	virtual void Release();
};


#endif // !__MOUSE_H__

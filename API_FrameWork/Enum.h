#pragma once

#ifndef __ENUM_H__
#define __ENUM_H__

namespace BULLET
{
	enum DIR { LEFT, RIGHT, UP, DOWN, DIR_END };
	enum SHAPE { CIRCLE, ELLIPSE, SHAPE_END };
}

namespace OBJID
{
	enum ID { PLAYER, MONSTER, BOSS, BULLET, MOUSE, END };
}

#endif // !__ENUM_H__

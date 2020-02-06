#pragma once

#ifndef __ENUM_H__
#define __ENUM_H__

namespace BULLET
{
	enum SHAPE { CIRCLE, ELLIPSE, SHAPE_END };
	enum DIR { LEFT, RIGHT, UP, DOWN, BASIC, DIR_END
	};
}

namespace OBJID
{
	enum ID { PLAYER, MONSTER, BOSS, BULLET, PLAYER_BULLET, MOUSE, END };
}
namespace BOSS
{
	enum STATE { P1_IDLE, END};
}
namespace MINIGUN
{
	enum ID { LEFT, RIGHT, END};
}


#endif // !__ENUM_H__
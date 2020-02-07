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
	enum STATE { INI, P1_IDLE, P1_A1_PRE ,P1_A1_S1, P1_A1_S2, P1_A1_S3,P2_IDLE, END};
}
namespace MINIGUN
{
	enum ID { LEFT, RIGHT, IEND};
	enum STATE { NORMAL, LOCKON, STATE_END};
}
namespace MAINGAME
{
	enum STATE { START, GAMEOVER, COMPLETE, END};
}


#endif // !__ENUM_H__
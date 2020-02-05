#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	// 좌표의 자료형을 float으로 설정한 이유는 수학적 연산이 들어갈 경우
	// 소수점 자리를 토대로 정밀한 연산을 하기 위해서 이다.
	float	fX;
	float	fY;

	// 크기는 소수점을 포함하여 정밀하게 그릴 필요가 없다.
	int		iCX;
	int		iCY;
}INFO;

#endif // !__STRUCT_H__

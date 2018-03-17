#pragma once
#include"Qt_CG_PRO1.h"
class Qt_CG_PRO1;
class JumpAbleClass
{
public:
	JumpAbleClass();
	~JumpAbleClass();

	void attach(Qt_CG_PRO1 *ui);
	Qt_CG_PRO1 *widget;

	void jump(float x, float z);
	float posX = 0;
	float posZ = 0;
	float posY = 2;
};


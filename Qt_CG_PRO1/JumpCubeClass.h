#pragma once
#include"Qt_CG_PRO1.h"
class Qt_CG_PRO1;
class JumpCubeClass
{
public:
	JumpCubeClass();
	~JumpCubeClass();
	void attach(Qt_CG_PRO1 *ui);

	Qt_CG_PRO1 *widget;

	int posX;
	int posZ;
	bool nextP; //true Ϊx�᷽��falseΪz�᷽��
	void ranPOS(int x, int z);
};


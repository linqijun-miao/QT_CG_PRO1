#include "JumpCubeClass.h"
#include<ctime>

JumpCubeClass::JumpCubeClass()
{
}


JumpCubeClass::~JumpCubeClass()
{
}
void JumpCubeClass::attach(Qt_CG_PRO1 *ui) {
	widget = ui;
}

void JumpCubeClass::ranPOS(int x, int z) {
	srand((unsigned)time(NULL));
	int xOrz = rand() % 2;
	if (xOrz == 0) {
		nextP = true;//x�᷽��
		posZ = z;
		posX = x + rand() % 4 + 3;

	}
	else {
		nextP = false;//z�᷽��
		posX = x;
		posZ = z + rand() % 4 + 3;
	}
}
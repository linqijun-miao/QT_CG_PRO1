#include "JumpAbleClass.h"



JumpAbleClass::JumpAbleClass()
{
}


JumpAbleClass::~JumpAbleClass()
{
}
void JumpAbleClass::attach(Qt_CG_PRO1 *ui) {
	widget = ui;
}

void JumpAbleClass::jump(float x, float z) {
	posX += x;
	posZ += z;
}
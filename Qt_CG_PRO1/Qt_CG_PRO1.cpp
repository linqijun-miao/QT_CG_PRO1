#include "Qt_CG_PRO1.h"
#include<gl\GLU.h>
#include"JumpCubeClass.h"
#include"JumpAbleClass.h"
#include<QKeyEvent>
#include<qtime>
Qt_CG_PRO1::Qt_CG_PRO1(QWidget *parent)
	: QOpenGLWidget(parent)
	
{
	jumper = new JumpAbleClass();
	jumper->attach(this);
	int count = 0;
	for (int i = 0; i < 4; i++) { //��ʼ���ĸ�����
		JumpCubeClass temp;
		temp.posX = count + 4;
		temp.posZ = 0;
		count += 4;
		temp.nextP = true;
		temp.attach(this);
		cubeList.insert(cubeList.end(), temp);
	}
	
	ui.setupUi(this);
}

void Qt_CG_PRO1::initializeGL() {
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               //��ɫ����  
	glShadeModel(GL_SMOOTH);                            //������Ӱƽ��  
	
	glClearDepth(1.0);                                  //������Ȼ���  
	glEnable(GL_DEPTH_TEST);                            //������Ȳ���  
	glDepthFunc(GL_LEQUAL);                             //������Ȳ��Ե�����  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //����ϵͳ��͸�ӽ�������  

	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //���������  
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //��ɢ�����  
	GLfloat LightPosition[] = { 0.0f, 0.0f, 6.0f, 1.0f }; //��Դλ��  
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //���û�����  
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //���������  
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //���ù�Դλ��  
	glEnable(GL_LIGHT1);                                //����һ�Ź�Դ  
	glEnable(GL_LIGHTING);  //����һ�Ź�Դ  
	setList();
}

void Qt_CG_PRO1::resizeGL(int w, int h) {
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect;


	if (w >= h) {
		aspect = w / h;
		glOrtho(-10 * aspect, 10 * aspect, -10, 10, -10, 10);
		
	}
	else {
		aspect = h / w;
		glOrtho(-10, 10, -10 * aspect, 10 * aspect, -10, 10);
		
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Qt_CG_PRO1::setList() {
	m_box = glGenLists(2);
	glNewList(m_box, GL_COMPILE);
	glBegin(GL_QUADS);                                 
														
	glVertex3f(1.0f, 1.0f, -1.0f);                  //����(����)  
	glVertex3f(-1.0f, 1.0f, -1.0f);                 //����(����)  
	glVertex3f(-1.0f, 1.0f, 1.0f);                  //����(����)  
	glVertex3f(1.0f, 1.0f, 1.0f);                   //����(����)  

													
	glVertex3f(1.0f, -1.0f, 1.0f);                  //����(����)  
	glVertex3f(-1.0f, -1.0f, 1.0f);                 //����(����)  
	glVertex3f(-1.0f, -1.0f, -1.0f);                //����(����)  
	glVertex3f(1.0f, -1.0f, -1.0f);                 //����(����)  

													
	glVertex3f(1.0f, 1.0f, 1.0f);                   //����(ǰ��)  
	glVertex3f(-1.0f, 1.0f, 1.0f);                  //����(ǰ��)  
	glVertex3f(-1.0f, -1.0f, 1.0f);                 //����(ǰ��)  
	glVertex3f(1.0f, -1.0f, 1.0f);                  //����(ǰ��)  

													
	glVertex3f(1.0f, -1.0f, -1.0f);                 //����(����)  
	glVertex3f(-1.0f, -1.0f, -1.0f);                //����(����)  
	glVertex3f(-1.0f, 1.0f, -1.0f);                 //����(����)  
	glVertex3f(1.0f, 1.0f, -1.0f);                  //����(����)  

													
	glVertex3f(-1.0f, 1.0f, 1.0f);                  //����(����)  
	glVertex3f(-1.0f, 1.0f, -1.0f);                 //����(����)  
	glVertex3f(-1.0f, -1.0f, -1.0f);                //����(����)  
	glVertex3f(-1.0f, -1.0f, 1.0f);                 //����(����)  

													 
	glVertex3f(1.0f, 1.0f, -1.0f);                  //����(����)  
	glVertex3f(1.0f, 1.0f, 1.0f);                   //����(����)  
	glVertex3f(1.0f, -1.0f, 1.0f);                  //����(����)  
	glVertex3f(1.0f, -1.0f, -1.0f);                 //����(����)  
	glEnd();
	glEndList();

	s_box = m_box + 1;
	glNewList(s_box, GL_COMPILE);
	glBegin(GL_QUADS);
	glVertex3f(0.5f, 0.5f, -0.5f);                  //����(����)  
	glVertex3f(-0.5f, 0.5f, -0.5f);                 //����(����)  
	glVertex3f(-0.5f, 0.5f, 0.5f);                  //����(����)  
	glVertex3f(0.5f, 0.5f, 0.5f);                   //����(����)  

													  
	glVertex3f(0.5f, -0.5f, 0.5f);                  //����(����)  
	glVertex3f(-0.5f, -0.5f, 0.5f);                 //����(����)  
	glVertex3f(-0.5f, -0.5f, -0.5f);                //����(����)  
	glVertex3f(0.5f, -0.5f, -0.5f);                 //����(����)  

													  
	glVertex3f(0.5f, 0.5f, 0.5f);                   //����(ǰ��)  
	glVertex3f(-0.5f, 0.5f, 0.5f);                  //����(ǰ��)  
	glVertex3f(-0.5f, -0.5f, 0.5f);                 //����(ǰ��)  
	glVertex3f(0.5f, -0.5f, 0.5f);                  //����(ǰ��)  

													  
	glVertex3f(0.5f, -0.5f, -0.5f);                 //����(����)  
	glVertex3f(-0.5f, -0.5f, -0.5f);                //����(����)  
	glVertex3f(-0.5f, 0.5f, -0.5f);                 //����(����)  
	glVertex3f(0.5f, 0.5f, -0.5f);                  //����(����)  

													  
	glVertex3f(-0.5f, 0.5f, 0.5f);                  //����(����)  
	glVertex3f(-0.5f, 0.5f, -0.5f);                 //����(����)  
	glVertex3f(-0.5f, -0.5f, -0.5f);                //����(����)  
	glVertex3f(-0.5f, -0.5f, 0.5f);                 //����(����)  

													 
	glVertex3f(0.5f, 0.5f, -0.5f);                  //����(����)  
	glVertex3f(0.5f, 0.5f, 0.5f);                   //����(����)  
	glVertex3f(0.5f, -0.5f, 0.5f);                  //����(����)  
	glVertex3f(0.5f, -0.5f, -0.5);                 //����(����)  
	glEnd();
	glEndList();

}

void Qt_CG_PRO1::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����Ļ����Ȼ���  
	
	for (iter = cubeList.begin(); iter != cubeList.end(); iter++) {

		GLfloat mat_ambient[] = { rand() % 3 + 0.1,rand() % 3 + 0.1,rand() % 3 + 0.1,1.0 };
		GLfloat mat_diffuse[] = { rand() % 3 + 0.1,rand() % 3 + 0.1,rand() % 3 + 0.1,1.0 };
	//	GLfloat mat_specular[] = { 1.0, 0.0, 1.0,1.0 };
		GLfloat mat_shininess[] = { 50.0 };

		GLfloat light_position[] = { 1.0, 1.0, 1.0,0.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		JumpCubeClass tCube = *iter;
		glLoadIdentity();
		gluLookAt(0, 3, 3, 0.0, 0, 0, 0, 1, 0);
		glRotatef(10, 0.0f, 1.0f, 0.0f);
		glTranslatef(tCube.posX-6, 0, tCube.posZ);
		glTranslatef(-offsetX, 0, -offsetZ);
		glCallList(m_box);
	}	
	glLoadIdentity();
	gluLookAt(0, 3, 3, 0.0, 0, 0, 0, 1, 0);
	glRotatef(10, 0.0f, 1.0f, 0.0f);
	glTranslatef(jumper->posX-6 , jumper->posY, jumper->posZ);
	glTranslatef(-offsetX, 0, -offsetZ);
	glCallList(s_box);

}

void  Qt_CG_PRO1::keyPressEvent(QKeyEvent *eventt) {
	switch (eventt->key()) {
	case Qt::Key_K:
		ss+=0.2;
		break;
	}
}

void sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void  Qt_CG_PRO1::keyReleaseEvent(QKeyEvent *eventt) {
	switch (eventt->key()) {
	case Qt::Key_K:
		if (onJump) {
			return;
		}
		if (!eventt->isAutoRepeat()) {
			onJump = true;
			float xOrZSpeed = ss / 10;
			if (xOrZSpeed > 0.5) {
				xOrZSpeed = 0.5f;
			}
			float ySpeed = 1.2;
			float preMove = 0.0;
			bool onOrDrop = false;//true means drop 

			do{// ����û�е���ȥ�����
				if (cubeList.at(cubeCount+1).nextP) {//x��
					jumper->posX += xOrZSpeed;//�ƶ�����
					preMove += xOrZSpeed;
					jumper->posY += ySpeed;
					update();
					ySpeed -= 0.1;
					sleep(10);
				}
				else {
					jumper->posZ += xOrZSpeed;
					preMove += xOrZSpeed;
					jumper->posY += ySpeed;
					update();
					ySpeed -= 0.1;
					sleep(10);
				}
			} while (jumper->posY >= 2.0f);

			if (cubeList.at(cubeCount+1).nextP) {
				if ((jumper->posX - cubeList.at(cubeCount).posX) <= 1) {
					
					onOrDrop = false;
				}
				else {
					if (((jumper->posX - cubeList.at(cubeCount + 1).posX) <= 1&& (jumper->posX - cubeList.at(cubeCount + 1).posX)>0)|| ((cubeList.at(cubeCount + 1).posX - jumper->posX) <= 1)&& (cubeList.at(cubeCount + 1).posX - jumper->posX) >0){
						float test = cubeList.at(cubeCount+1).posX;
						onOrDrop = false;
						cubeCount++;
						JumpCubeClass last = cubeList.at(cubeList.size()-1);
						JumpCubeClass newCube;
						newCube.ranPOS(last.posX, last.posZ);
						newCube.attach(this);
						cubeList.insert(cubeList.end(), newCube);
					}
					else {
						onOrDrop = true;
					}
				}
			}
			else {
				if ((jumper->posZ - cubeList.at(cubeCount).posZ) <= 1) {
					onOrDrop = false;
				}
				else {
					if (((jumper->posZ - cubeList.at(cubeCount + 1).posZ) <= 1 && (jumper->posZ - cubeList.at(cubeCount + 1).posZ)>0) || ((cubeList.at(cubeCount + 1).posZ - jumper->posZ) <= 1) && (cubeList.at(cubeCount + 1).posZ - jumper->posZ) >0) {
						onOrDrop = false;
						cubeCount++;
						JumpCubeClass last = cubeList.at(cubeList.size()-1);
						JumpCubeClass newCube;
						newCube.ranPOS(last.posX, last.posZ);
						newCube.attach(this);
						cubeList.insert(cubeList.end(),newCube);
					}
					else {
						onOrDrop = true;
					}
				}
			}
			if (onOrDrop) {
				do {
					//�Ҳ���
						jumper->posY += ySpeed;
						update();
						ySpeed -= 0.1;
						sleep(10);			
				} while (jumper->posY >= 0.0f);
			}


			ss = 0.0;
			jumper->posY = 2;
			if (cubeList.at(cubeCount+1).nextP) {//�ƶ���ͷ
				float tempOffset = offsetX + preMove;
				while (offsetX <= tempOffset) {
					offsetX += 0.1;
					update();
					sleep(1);
				}
			}
			else {
				float tempOffset = offsetZ + preMove;
				while (offsetZ <= tempOffset) {
					offsetZ += 0.1;
					update();
					sleep(1);
				}
			}
			


			onJump = false;
		}
		
		break;
	}
}
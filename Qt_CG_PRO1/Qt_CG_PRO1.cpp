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
		glCallList(m_box);
	}	
	glLoadIdentity();
	gluLookAt(0, 3, 3, 0.0, 0, 0, 0, 1, 0);
	glRotatef(10, 0.0f, 1.0f, 0.0f);
	glTranslatef(jumper->posX-6+4 , 2, jumper->posZ);
	glCallList(s_box);

}

void  Qt_CG_PRO1::keyPressEvent(QKeyEvent *eventt) {
	switch (eventt->key()) {
	case Qt::Key_K:
		ss++;
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
		if (!eventt->isAutoRepeat()) {
			float xOrZSpeed = ss / 10;
			float ySpeed = 0.6;
			while (ySpeed > 0) {
				
			}
		}

		break;
	}
}
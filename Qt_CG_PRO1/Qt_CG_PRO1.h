#pragma once

#include <QtWidgets/QWidget>
#include<qopenglwidget.h>
#include "ui_Qt_CG_PRO1.h"
#include"JumpCubeClass.h"
#include"JumpAbleClass.h"
#include<vector>
using namespace std;
class JumpAbleClass;
class JumpCubeClass;
class Qt_CG_PRO1 : public QOpenGLWidget
{
	Q_OBJECT

public:
	Qt_CG_PRO1(QWidget *parent = Q_NULLPTR);
	void setList();
	GLuint m_box;
	GLuint s_box;
	vector<JumpCubeClass> cubeList;
	vector<JumpCubeClass>::iterator iter;
	float offsetX = 0;
	float offsetZ = 0;
	JumpAbleClass *jumper;
	float ss = 0.0;

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event); 
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
private:
	Ui::Qt_CG_PRO1Class ui;
};

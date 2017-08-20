#include "Display.h"
#include "GlUtil.h"

Display::Display(QWidget* parent) : QOpenGLWidget(parent)
{

}

Display::~Display() {}

void Display::initializeGL()
{
	stdInitializeGL();
}

void Display::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float x1, y1, x2, y2;
	float angle;
	double radius = 0.1;

	x1 = 0.5, y1 = 0.5;
	glColor3f(0, 0, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle<361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void Display::resizeGL(int w, int h)
{
	stdResizeGL(w, h);
}
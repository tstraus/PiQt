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

	drawCircle(Vec2f(-2.0f, -2.0f), 4.0f);
	drawFilledCircle(Vec2f(0.0f, 0.0f), 0.1f);
}

void Display::resizeGL(int w, int h)
{
	stdResizeGL(w, h);
}
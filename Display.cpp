#include "Display.h"

Display::Display(QWidget* parent) : QOpenGLWidget(parent)
{
	stdClearGL();

	drawCircle(Vec2f(-2.0f, -2.0f), 4.0f); // the circle we're comparing against to calculate pi
}

Display::~Display() {}

void Display::initializeGL()
{
	stdInitializeGL();
}

void Display::addPoints(vector<Vec2f> points)
{
	for (auto& point : points) // check if it's in the circle, draw green if yes, red if not
		drawFilledCircle(point, 0.01f);
}

void Display::reset()
{
	stdClearGL();
}

void Display::resizeGL(int w, int h)
{
	stdResizeGL(w, h);
}
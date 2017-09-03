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

void Display::addPoints(vector<pair<Vec2f, Color>> points)
{
	for (auto& point : points) // check if it's in the circle, draw green if yes, red if not
		drawFilledCircle(Vec2f(point.first.x * 4.0f - 2.0f, point.first.y * 4.0f - 2.0f), 0.01f, point.second);
}

void Display::reset()
{
	stdClearGL();
}

void Display::resizeGL(int w, int h)
{
	stdResizeGL(w, h);
}

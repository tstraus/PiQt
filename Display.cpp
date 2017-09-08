#include "Display.h"
#include <iostream>

using namespace std;

Display::Display(QWidget* parent) : QOpenGLWidget(parent) {}

Display::~Display() {}

void Display::initializeGL()
{
	stdInitializeGL();

	//stdClearGL();

	drawCircle(Vec2f(-2.0f, -2.0f), 4.0f); // the circle we're comparing against to calculate pi
}

void Display::addPoints(vector<pair<Vec2f, Color>> points)
{
	drawFilledCircle(Vec2f(0.5f, 0.5f), 0.1f, RED);

	for (auto& point : points) // check if it's in the circle, draw green if yes, red if not
	{
		//cout << "x: " << point.first.x << ", y: " << point.first.y << endl;

		drawFilledCircle(Vec2f(point.first.x, point.first.y), 0.1f, point.second);
		//drawFilledCircle(Vec2f(point.first.x * 4.0f - 2.0f, point.first.y * 4.0f - 2.0f), 0.01f, point.second);
	}
}

void Display::reset()
{
	stdClearGL();
}

void Display::resizeGL(int w, int h)
{
	stdResizeGL(w, h);
}

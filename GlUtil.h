#ifndef __GL_UTIL_H__
#define __GL_UTIL_H__

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <math.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

struct Vec2f
{
	float x;

	float y;

	Vec2f() {};

	Vec2f(float x, float y) : x(x), y(y) {};
};

struct Vec3f
{
	float x;

	float y;

	float z;

	Vec3f() {};

	Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};
};

struct Color
{
	float r;

	float g;

	float b;

	Color() {};

	Color(float r, float g, float b) : r(r), g(g), b(b) {};
};

#define BLACK              Color(0.0f, 0.0f, 0.0f)
#define DARKER_DARK_GRAY   Color(0.15f, 0.15f, 0.15f)
#define DARK_GRAY          Color(0.3f, 0.3f, 0.3f)
#define LIGHTER_DARK_GRAY  Color(0.4f, 0.4f, 0.4f)
#define GRAY               Color(0.5f, 0.5f, 0.5f)
#define DARKER_LIGHT_GRAY  Color(0.6f, 0.6f, 0.6f)
#define LIGHT_GRAY         Color(0.7f, 0.7f, 0.7f)
#define LIGHTER_LIGHT_GRAY Color(0.85f, 0.85f, 0.85f)
#define WHITE              Color(1.0f, 1.0f, 1.0f)
#define RED                Color(1.0f, 0.0f, 0.0f)
#define GREEN              Color(0.0f, 1.0f, 0.0f)
#define BLUE               Color(0.0f, 0.0f, 1.0f)
#define YELLOW             Color(1.0f, 1.0f, 0.0f)
#define CYAN               Color(0.0f, 1.0f, 1.0f)
#define MAGENTA            Color(1.0f, 0.0f, 1.0f)
#define ORANGE             Color(1.0f, 0.6f, 0.0f)
#define LIME               Color(0.6f, 1.0f, 0.0f)
#define AQUA               Color(0.0f, 1.0f, 0.6f)
#define AZURE              Color(0.0f, 0.6f, 1.0f)
#define VIOLET             Color(0.6f, 0.0f, 1.0f)
#define ROSE               Color(1.0f, 0.0f, 0.6f)

#ifdef QT_CORE_LIB
inline float maxHeight(QWidget* window)
{
	return window->height() / 100.0f;
}

inline float maxWidth(QWidget* window)
{
	return window->width() / 100.0f;
}
#endif // QT_CORE_LIB

inline float convertFromPercentHeight(float position, float yMax)
{
	return position * 2.0f * yMax - yMax;
}

inline float convertFromPercentWidth(float position, float xMax)
{
	return position * 2.0f * xMax - xMax;
}

inline void stdInitializeGL(Color color = Color(1.0f, 1.0f, 1.0f))
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

inline void stdResizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.01, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

inline void stdClearGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void drawLine(Vec2f start, Vec2f end, float lineWidth = 1.0f, Color color = BLACK)
{
	glLineWidth(lineWidth);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();
}

inline void drawHorizontalLine(float percent, float xMax, float yMax, float lineWidth = 1.0f, Color color = BLACK)
{
	drawLine(Vec2f(-xMax, convertFromPercentHeight(percent, yMax)), Vec2f(xMax, convertFromPercentHeight(percent, yMax)), lineWidth, color);
}

inline void drawVerticalLine(float percent, float xMax, float yMax, float lineWidth = 1.0f, Color color = BLACK)
{
	drawLine(Vec2f(convertFromPercentWidth(percent, xMax), -yMax), Vec2f(convertFromPercentWidth(percent, xMax), yMax), lineWidth, color);
}

inline void drawGraph(float xMax, float yMax, float lineWidth = 1.0f, Color color = BLACK)
{
	drawLine(Vec2f(-xMax, 0.0f), Vec2f(xMax, 0.0f), lineWidth, color);
	drawLine(Vec2f(0.0f, -yMax), Vec2f(0.0f, yMax), lineWidth, color);
}

inline void drawCircle(Vec2f position, float radius = 0.1f, float lineWidth = 1.0f, Color color = BLACK)
{
	glLineWidth(lineWidth);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
		glVertex2f(cos(i * 0.0174533) * radius + position.x, sin(i * 0.0174533) * radius + position.y);
	glEnd();
}

inline void drawFilledCircle(Vec2f center, float radius = 1.0f, Color color = BLACK)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(center.x, center.y);
	for (float angle = 1.0f; angle < 361.0f; angle += 0.2f)
		glVertex2f(center.x + sin(angle) * radius, center.y + cos(angle) * radius);
	glEnd();
}

inline void drawRectangle(Vec2f topLeft, Vec2f topRight, Vec2f bottomLeft, Vec2f bottomRight, float lineWidth = 1.0f, Color color = BLACK)
{
	drawLine(topLeft, topRight, lineWidth, color);
	drawLine(topRight, bottomRight, lineWidth, color);
	drawLine(bottomRight, bottomLeft, lineWidth, color);
	drawLine(bottomLeft, topLeft, lineWidth, color);
}

inline void drawRectangle(Vec2f bottomLeft, Vec2f topRight, float lineWidth = 1.0f, Color color = BLACK)
{
	drawRectangle(Vec2f(bottomLeft.x, topRight.y), topRight, bottomLeft, Vec2f(topRight.x, bottomLeft.y), lineWidth, color);
}

inline void drawRectangle(Vec2f center, float xMax, float yMax, float lineWidth = 1.0f, Color color = BLACK)
{
	drawRectangle(Vec2f(center.x - xMax / 2.0f, center.y + yMax / 2.0f), Vec2f(center.x + xMax / 2.0f, center.y + yMax / 2.0f), Vec2f(center.x - xMax / 2.0f, center.y - yMax / 2.0f), Vec2f(center.x + xMax / 2.0f, center.y - yMax / 2.0f), lineWidth, color);
}

inline void drawRectangle(float bottomPercent, float topPercent, float xMax, float yMax, float lineWidth = 1.0f, Color color = BLACK)
{
	drawRectangle(Vec2f(-xMax, convertFromPercentHeight(bottomPercent, yMax)), Vec2f(xMax, convertFromPercentHeight(topPercent, yMax)), lineWidth, color);
}

inline void drawFilledRectangle(Vec2f topLeft, Vec2f topRight, Vec2f bottomLeft, Vec2f bottomRight, Color color = BLACK)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_TRIANGLES);
	glVertex2f(topRight.x, topRight.y);
	glVertex2f(topLeft.x, topLeft.y);
	glVertex2f(bottomLeft.x, bottomLeft.y);

	glVertex2f(topRight.x, topRight.y);
	glVertex2f(bottomLeft.x, bottomLeft.y);
	glVertex2f(bottomRight.x, bottomRight.y);
	glEnd();
}

inline void drawFilledRectangle(Vec2f bottomLeft, Vec2f topRight, Color color = BLACK)
{
	drawFilledRectangle(Vec2f(bottomLeft.x, topRight.y), topRight, bottomLeft, Vec2f(topRight.x, bottomLeft.y), color);
}

inline void drawFilledRectangle(Vec2f center, float xMax, float yMax, Color color = BLACK)
{
	drawFilledRectangle(Vec2f(center.x - xMax / 2.0f, center.y + yMax / 2.0f), Vec2f(center.x + xMax / 2.0f, center.y + yMax / 2.0f), Vec2f(center.x - xMax / 2.0f, center.y - yMax / 2.0f), Vec2f(center.x + xMax / 2.0f, center.y - yMax / 2.0f), color);
}

inline void drawFilledRectangle(float bottomPercent, float topPercent, float xMax, float yMax, Color color = BLACK)
{
	drawFilledRectangle(Vec2f(-xMax, convertFromPercentHeight(bottomPercent, yMax)), Vec2f(xMax, convertFromPercentHeight(topPercent, yMax)), color);
}

inline void drawGradient(Vec2f topLeft, Vec2f topRight, Vec2f bottomLeft, Vec2f bottomRight, Color start = BLACK, Color end = BLACK)
{
	Vec2f middleLeft((topLeft.x + bottomLeft.x) / 2.0f, (topLeft.y + bottomLeft.y) / 2.0f);
	Vec2f middleRight((topRight.x + bottomRight.x) / 2.0f, (topRight.y + bottomRight.y) / 2.0f);
	Color middle((start.r + end.r) / 2.0f, (start.g + end.g) / 2.0f, (start.b + end.b) / 2.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(start.r, start.g, start.b);
	glVertex2f(topRight.x, topRight.y);
	glVertex2f(topLeft.x, topLeft.y);
	glColor3f(middle.r, middle.g, middle.b);
	glVertex2f(middleLeft.x, middleLeft.y);

	glVertex2f(middleLeft.x, middleLeft.y);
	glVertex2f(middleRight.x, middleRight.y);
	glColor3f(start.r, start.g, start.b);
	glVertex2f(topRight.x, topRight.y);

	glColor3f(middle.r, middle.g, middle.b);
	glVertex2f(middleRight.x, middleRight.y);
	glVertex2f(middleLeft.x, middleLeft.y);
	glColor3f(end.r, end.g, end.b);
	glVertex2f(bottomLeft.x, bottomLeft.y);

	glVertex2f(bottomLeft.x, bottomLeft.y);
	glVertex2f(bottomRight.x, bottomRight.y);
	glColor3f(middle.r, middle.g, middle.b);
	glVertex2f(middleRight.x, middleRight.y);
	glEnd();
}

inline void drawGradient(Vec2f bottomLeft, Vec2f topRight, Color start = WHITE, Color end = BLACK)
{
	drawGradient(Vec2f(bottomLeft.x, topRight.y), topRight, bottomLeft, Vec2f(topRight.x, bottomLeft.y), start, end);
}

inline void drawGradient(Vec2f center, float xMax, float yMax, Color start = Color(1.0f, 1.0f, 1.0f), Color end = BLACK)
{
	drawGradient(Vec2f(center.x - xMax / 2.0f, center.y + yMax / 2.0f), Vec2f(center.x + xMax / 2.0f, center.y + yMax / 2.0f), Vec2f(center.x - xMax / 2.0f, center.y - yMax / 2.0f), Vec2f(center.x + xMax / 2.0f, center.y - yMax / 2.0f), start, end);
}

inline void drawGradient(float bottomPercent, float topPercent, float xMax, float yMax, Color bottomColor = WHITE, Color topColor = BLACK)
{
	drawGradient(Vec2f(-xMax, convertFromPercentHeight(bottomPercent, yMax)), Vec2f(xMax, convertFromPercentHeight(topPercent, yMax)), topColor, bottomColor);
}


#endif // __GL_UTIL_H__

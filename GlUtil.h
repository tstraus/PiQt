#ifndef __GL_UTIL_H__
#define __GL_UTIL_H__

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

struct Vec2f
{
	Vec2f() {};

	Vec2f(float x, float y) : x(x), y(y) {};

	float x;

	float y;
};

struct Vec3f
{
	Vec3f() {};

	Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};

	float x;

	float y;

	float z;
};

struct Color
{
	Color() {};

	Color(float r, float g, float b) : r(r), g(g), b(b) {};

	float r;

	float g;

	float b;
};

inline void stdInitializeGL(Color color = Color(1.0f, 1.0f, 1.0f))
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
};

inline void stdResizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.01, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
};

inline void drawCircle(Vec2f center, float radius = 1.0f, Color color = Color(0.0f, 0.0f, 0.0f), int num_segments = 360)
{
	float theta;

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < num_segments; i++)
	{
		theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
		glVertex2f(radius * cosf(theta) + center.x, radius * sinf(theta) + center.y);
	}

	glEnd();
};

inline void drawFilledCircle(Vec2f center, float radius = 1.0f, Color color = Color(0.0f, 0.0f, 0.0f))
{
	glColor3f(color.r, color.g, color.b);

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(center.x, center.y);

	for (float angle = 1.0f; angle < 361.0f; angle += 0.2f)
		glVertex2f(center.x + sin(angle) * radius, center.y + cos(angle) * radius);

	glEnd();
};

#endif // __GL_UTIL_H__
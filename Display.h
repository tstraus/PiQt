#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <QOpenGlWidget>
#include <vector>

#include "GlUtil.h"

using std::vector;

class Display : public QOpenGLWidget
{
public:
	Display(QWidget* parent = 0);

	~Display();

	void addPoints(vector<Vec2f> points);

	void reset();

protected:
	void initializeGL();

	void resizeGL(int w, int h);
};

#endif // __DISPLAY_H__
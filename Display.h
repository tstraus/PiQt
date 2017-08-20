#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <QOpenGlWidget>

class Display : public QOpenGLWidget
{
public:
	Display(QWidget* parent = 0);

	~Display();

protected:
	void initializeGL();

	void resizeGL(int w, int h);

	void paintGL();
};

#endif // __DISPLAY_H__
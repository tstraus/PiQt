#include <QOpenGlWidget>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

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

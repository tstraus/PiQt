#include <QOpenGlWidget>
#include <gl/GLU.h>
#include <gl/GL.h>

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
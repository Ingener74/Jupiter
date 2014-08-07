/*
 * GLViewer.h
 *
 *  Created on: Aug 4, 2014
 *      Author: pavel
 */

#ifndef GLVIEWER_H_
#define GLVIEWER_H_

#include <QtOpenGL/QGLWidget>

class GLViewer: public QGLWidget
{
Q_OBJECT
public:
	GLViewer();
	virtual ~GLViewer();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

#endif /* GLVIEWER_H_ */

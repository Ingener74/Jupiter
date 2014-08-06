/*
 * GLViewer.h
 *
 *  Created on: Aug 4, 2014
 *      Author: pavel
 */

#ifndef GLVIEWER_H_
#define GLVIEWER_H_

#include <QtWidgets/QWidget>

class GLViewer: public QGLWidget
{
	Q_OBJECT
public:
	GLViewer();
	virtual ~GLViewer();
};

#endif /* GLVIEWER_H_ */

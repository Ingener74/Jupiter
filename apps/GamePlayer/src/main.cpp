/*
 * main.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

void display(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.4f, 0.2f, 1.f);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{
	try
	{
		cout << "Game player" << endl;

		/*
		 * read program from lua file
		 *
		 *  -- set viewport
		 *  -- set ortho projection
		 *  -- create engine
		 */

		int windowWidth = 800, windowHeight = 600;

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(windowWidth, windowHeight);
		glutCreateWindow("Jupiter game player");

		glutReshapeFunc(reshape);
		glutDisplayFunc(display);
		glutIdleFunc(display);

		if (glewInit() != GLEW_OK) throw runtime_error("glew init error");

		glutMainLoop();

		return EXIT_SUCCESS;
	}
	catch ( exception const & e )
	{
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
}


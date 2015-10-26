/*
 * test-4.cpp
 *
 *  Created on: 24 авг. 2015 г.
 *      Author: Pavel
 */

#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#ifdef EMSCRIPTEN
    #include <GL/glut.h>
#elif __APPLE__
	#include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

using namespace std;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(.1f, .3f, .1f, 1.f);

    glutSwapBuffers();
}

void timer(int time) {

    glutPostRedisplay();

    int delay = 1000 / 30;
    glutTimerFunc(delay, timer, 0);
}

int main(int argc, char* argv[]) {

    try {
        int width = 640, height = 480;

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);

        glutCreateWindow("Test 4");

        glewExperimental = GL_TRUE;
        auto glewInitError = glewInit();
        if (glewInitError != GLEW_OK)
            throw runtime_error(
                "glew init error " + string(reinterpret_cast<const char*>(glewGetErrorString(glewInitError))));

        {
            cout << "OpenGL vendor:                     " << glGetString(GL_VENDOR) << endl;
            cout << "OpenGL renderer:                   " << glGetString(GL_RENDERER) << endl;
            cout << "OpenGL version:                    " << glGetString(GL_VERSION) << endl;
            cout << "OpenGL shading language version:   " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
            //            cout << "OpenGL extensions:                 " << glGetString(GL_EXTENSIONS) << endl;
        }

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
//        glutMouseFunc(mouse);
//        glutMotionFunc(mouseMove);
//        glutKeyboardFunc(key);
//        glutSpecialFunc(specKey);

//        glutFullScreen();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        reshape(width, height);
//        init();

        glutTimerFunc(0, timer, 0);
        glutMainLoop();

//        deinit();

        return EXIT_SUCCESS;
    } catch (exception const & e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return 0;
}


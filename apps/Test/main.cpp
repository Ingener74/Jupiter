/*
 * main.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: pavel
 */

#include "main.h"

using namespace std;

string base;

float w = 400.f, h = 240.f, m = 1.f;
float width = w * m, height = h * m;

int main(int argc, char **argv) {
    try {
        if(argc < 2)
            throw invalid_argument("usage: ./Test <path-to-resource>");

        base = argv[1];

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);

        // Для OpenGL 3.3
        glutInitContextVersion(3, 3);
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
        glutInitContextProfile(GLUT_CORE_PROFILE);

        glutCreateWindow("Test");

        glewExperimental = GL_TRUE;
        auto glewInitError = glewInit();
        if (glewInitError != GLEW_OK)
            throw runtime_error("glew init error " + string(reinterpret_cast<const char*>(glewGetErrorString(glewInitError))));

        {
            cout << "OpenGL vendor:                     " << glGetString(GL_VENDOR) << endl;
            cout << "OpenGL renderer:                   " << glGetString(GL_RENDERER) << endl;
            cout << "OpenGL version:                    " << glGetString(GL_VERSION) << endl;
            cout << "OpenGL shading language version:   " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
//            cout << "OpenGL extensions:                 " << glGetString(GL_EXTENSIONS) << endl;
        }

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);
        glutKeyboardFunc(key);
        glutSpecialFunc(specKey);

//        glutFullScreen();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        reshape(width, height);
        init();

        glutTimerFunc(0, timer, 0);
        glutMainLoop();

        deinit();

        return EXIT_SUCCESS;
    } catch (exception const & e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}

string getBase() {
    return base;
}


void timer(int time) {

    glutPostRedisplay();

    int delay = 1000 / 30;
    glutTimerFunc(delay, timer, 0);
}

void mouse(int button, int action, int x, int y) {
}

void mouseMove(int x, int y) {
}

void key(unsigned char k, int x, int y) {
    if (k == 27)
        glutLeaveMainLoop();
}

void specKey ( int key, int x, int y ){
}





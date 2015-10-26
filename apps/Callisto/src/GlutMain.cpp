/*
 * GlutMain.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: pavel
 */

#include "GamePlayer.h"
#ifdef EMSCRIPTEN
    #include <GL/glut.h>
#elif __APPLE__
	#include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

using namespace std;

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.3f, 0.1f, 1.f);

    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void mouse(int button, int action, int x, int y) {
    static map<int, string> buttons{
        { GLUT_LEFT_BUTTON, "GLUT_LEFT_BUTTON" },
        { GLUT_MIDDLE_BUTTON, "GLUT_MIDDLE_BUTTON" },
        { GLUT_RIGHT_BUTTON, "GLUT_RIGHT_BUTTON" },
    };
    static map<int, string> actions{
        { GLUT_DOWN, "GLUT_DOWN" },
        { GLUT_UP, "GLUT_UP" }
    };

    input();
}

void mouseMove(int x, int y) {
    input();
}

void keyboardFunc(uint8_t key, int x, int y){
    keyboard(key);
}

void timer(int time){

    glutPostRedisplay();

    int delay = 1000 / 30;
    glutTimerFunc(delay, timer, 0);
}

int main(int argc, char **argv) {
    try {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(800, 480);
        glutCreateWindow(getTitle().c_str());

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);
        glutKeyboardFunc(keyboardFunc);

        if (glewInit() != GLEW_OK)
            throw runtime_error("glew init error");

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        createGame(argc, argv);

        glutReshapeWindow(getWidth(), getHeight());
        glViewport(0, 0, getWidth(), getHeight());

        glutTimerFunc(0, timer, 0);

        glutMainLoop();

        return EXIT_SUCCESS;
    } catch (std::exception const & e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}




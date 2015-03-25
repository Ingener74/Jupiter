/*
 * GlutMain.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: pavel
 */

#include "GamePlayer.h"
#include <GL/glut.h>

using namespace std;

void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.3f, 0.1f, 1.f);

    myDraw();

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

    myInput();
}

void mouseMove(int x, int y) {
    myInput();
}

int main(int argc, char **argv) {
    try {
//        cout << title << endl;

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(800, 480);
        glutCreateWindow(getTitle().c_str());

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);

        if (glewInit() != GLEW_OK)
            throw runtime_error("glew init error");

        if (!myCreateGame(argc, argv))
            throw runtime_error("can't create game");
//        if(!myCreateGameWithJsonFile(argc, argv))
//            throw runtime_error("can't create game");

        glutReshapeWindow(getWidth(), getHeight());
        glViewport(0, 0, getWidth(), getHeight());

        glutMainLoop();

        return EXIT_SUCCESS;
    } catch (std::exception const & e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}




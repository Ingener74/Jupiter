/*
 * GLFWMain.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: pavel
 */

#include <iostream>
#include <sstream>

#include "GamePlayer.h"
#include <GLFW/glfw3.h>

using namespace std;

template<typename T>
string to_string(T t){
    stringstream s;
    s << t;
    return s.str();
}

void myErrorFun(int errorCode, const char* description) {
    throw runtime_error(to_string(errorCode) + " " + description);
}

void myKeyFun(GLFWwindow* window, int key, int scancode, int action, int mods) {
    input();
}

int main(int argc, char **argv) {
    try {
        glfwSetErrorCallback(myErrorFun);

        if(!glfwInit())
            throw runtime_error("can't init GLFW");

//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//        glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_FORWARD_COMPAT);

        auto window = glfwCreateWindow(800, 480, getTitle().c_str(), nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw runtime_error("can't create window");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1000);

//        if (glewInit() != GLEW_OK)
//            throw runtime_error("glew init error");

        glfwSetKeyCallback(window, myKeyFun);

        createGame(argc, argv);

        glfwSetWindowSize(window, getWidth(), getHeight());
        glViewport(0, 0, getWidth(), getHeight());

        while (!glfwWindowShouldClose(window)) {
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.f, 0.f, 0.f, 1.f);

            draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}




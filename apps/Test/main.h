/*
 * main.h
 *
 *  Created on: Apr 13, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_MAIN_H_
#define APPS_TEST_MAIN_H_

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <climits>

#include <GL/glew.h>
//#ifdef  _WIN32
//    #include <GL/wglew.h>
//#else
//    #include <GL/glxew.h>
//#endif

//#include <GL/gl.h>
//#include <GL/glext.h>

#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>
//#include <GL/freeglut_std.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shaders.h"
#include "Tools.h"

std::string getBase();

void mouse(int button, int action, int x, int y);
void mouseMove(int x, int y);
void key(unsigned char key, int x, int y);
void specKey(int key, int x, int y);
void timer(int time);

void reshape(int w, int h);
void init();
void display(void);
void deinit();

#endif /* APPS_TEST_MAIN_H_ */

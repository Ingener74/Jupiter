/*
 * Tools.h
 *
 *  Created on: Apr 2, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_TOOLS_H_
#define APPS_TEST_TOOLS_H_

#include <iostream>
#include <glm/glm.hpp>

using glm::mat4;
using std::ostream;

ostream& operator<<(ostream& out, const mat4& r);

#endif /* APPS_TEST_TOOLS_H_ */

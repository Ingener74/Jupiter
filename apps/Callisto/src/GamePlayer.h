/*
 * GamePlayer.h
 *
 *  Created on: Mar 25, 2015
 *      Author: pavel
 */

#ifndef APPS_CALLISTO_SRC_GAMEPLAYER_H_
#define APPS_CALLISTO_SRC_GAMEPLAYER_H_

#include <map>
#include <memory>
#include <fstream>
#include <iterator>
#include <iostream>
#include <stdexcept>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

bool createGame(int argc, char* argv[]);

bool createGameDirect(const boost::program_options::variables_map& vm);
bool createGameJsonFile(const boost::program_options::variables_map& vm);
void draw();
void input();
void keyboard(uint8_t key);

std::string getTitle();
int getWidth();
int getHeight();

#endif /* APPS_CALLISTO_SRC_GAMEPLAYER_H_ */

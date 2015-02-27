/*
 * JsonGame.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Jupiter/File.h"
#include "Jupiter/JsonNode.h"
#include "Jupiter/JsonGame.h"

namespace jupiter {

using namespace std;
using namespace glm;

JsonGame::JsonGame(const std::string& fileName) {

    unique_ptr<File> file(new File(fileName));

    using namespace boost::property_tree;

    ptree pt;

    json_parser::read_json(file->file(), pt);

    width = pt.get<int>("resolution.width");
    height = pt.get<int>("resolution.height");
    render = {ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100)};

    auto rootNode = pt.get_child("node");

    node = Aware::create<JsonNode>(rootNode);
}

JsonGame::~JsonGame() {
}

} /* namespace jupiter */

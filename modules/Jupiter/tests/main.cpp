/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: pavel
 */

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../src/JsonGameHolder.h"

#include <gtest/gtest.h>

using namespace std;
using namespace jupiter;

TEST(TestCase1, Test1){

    boost::property_tree::ptree pt;

    EXPECT_THROW(boost::property_tree::json_parser::read_json("../../Asteroids.json", pt), std::exception);

    JsonGameHolder::instance()->setGame(pt);

    EXPECT_EQ(1, 1);

    auto rootNode = JsonGameHolder::instance()->findNode("node", "root");
    EXPECT_STREQ("root", rootNode.get<string>("name").c_str());
}


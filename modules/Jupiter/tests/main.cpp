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

TEST(TestCase1, Test1)
{
    using namespace boost::property_tree;
    using namespace boost::property_tree::json_parser;

    ptree pt;

    read_json("/home/pavel/prj/Jupiter/samples/Asteroids/Asteroids.json", pt);

//    JsonGameHolder::instance()->setGame(pt);
//
//    auto rootNode = JsonGameHolder::instance()->findNode("node", "root");
//    EXPECT_STREQ("root", rootNode.get<string>("name").c_str());

//    auto rootNode = JsonGameHolder::instance()->findNode("node", "root");
//    EXPECT_STREQ("root", rootNode.get<string>("name").c_str());
//
//    auto rootNode = JsonGameHolder::instance()->findNode("node", "root");
//    EXPECT_STREQ("root", rootNode.get<string>("name").c_str());
//
//    auto rootNode = JsonGameHolder::instance()->findNode("node", "root");
//    EXPECT_STREQ("root", rootNode.get<string>("name").c_str());
}


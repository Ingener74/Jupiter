/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: pavel
 */

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <gtest/gtest.h>

#include "Jupiter.h"

using namespace std;
using namespace jupiter;

class JupiterTest: public testing::Test {
public:
    void SetUp() {
    }

    void TearDown() {
    }
};

TEST_F(JupiterTest, Aware) {
    auto node = Aware::create<Node>("test");
    ASSERT_EQ(Aware::objectsCount(), 1);

    auto node1 = new Node("test2");
    ASSERT_EQ(Aware::objectsCount(), 2);
    ASSERT_EQ(Aware::get<Node>("test2"), node1);

    delete node1;
    ASSERT_EQ(Aware::objectsCount(), 1);
}

TEST_F(JupiterTest, Node) {
    ASSERT_EQ(Aware::get<Node>("test")->setPosition(100.0, 0.0, 0.0)->getPositionX(), 100.0);
}


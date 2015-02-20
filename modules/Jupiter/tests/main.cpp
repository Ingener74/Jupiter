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

using namespace std;
using namespace jupiter;

TEST(TestCase1, Test1) {
    using namespace boost::property_tree;
    using namespace boost::property_tree::json_parser;

    ASSERT_EQ(1, 1);
}

TEST(TestAware1, TestAdd) {
    ASSERT_EQ(1, 1);
}


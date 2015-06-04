/*
 * test.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: pavel
 */

#include "test.h"

#include <iostream>
#include <fstream>

#include <json.hpp>

using namespace std;
using namespace nlohmann;

test::test() {
    try {
        fstream file("/home/pavel/workspace/Jupiter/samples/Box/Resources/Box.json");
        json j;
        file >> j;
        cout << j << endl;

        for (auto const& i : j["rigidBodies"]) {
            cout << i["name"] << endl;
        }

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}

test::~test() {
}


/*
 * main.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: pavel
 */

#include <iostream>

#include "test.h"

using namespace std;

int main(int argc, char **argv) {
    try {

        test t;

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}


/*
 * test-4.cpp
 *
 *  Created on: 24 авг. 2015 г.
 *      Author: Pavel
 */

#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char* argv[]) {
    try {
        return 0;
    } catch (exception const & e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}


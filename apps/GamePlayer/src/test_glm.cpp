/*
 * test_glm.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#include <iostream>

#include <glm/glm.hpp>

using namespace std;

int main(int argc, char **argv) {
    try {

        glm::mat4x4 m;

        float* p = reinterpret_cast<float*>(&m);

        for (int i = 0, n = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j, ++n) {
                cout << p[n] << " ";
            }
            cout << endl;
        }


    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}


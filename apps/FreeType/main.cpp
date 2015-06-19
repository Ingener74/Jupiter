/*
 * main.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: pavel
 */

#include <iostream>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

using namespace std;

int main(int argc, char **argv) {
    try {
        FT_Library library;
        FT_Init_FreeType(&library);
    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}


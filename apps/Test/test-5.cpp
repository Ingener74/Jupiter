/*
 * test-4.cpp
 *
 *  Created on: 24 авг. 2015 г.
 *      Author: Pavel
 */

#include <iostream>
#include <stdexcept>
#include <emscripten/emscripten.h>

//#include "lodepng.h"

using namespace std;

/*
em++ ../../../apps/Test/test-5.cpp -s ASYNCIFY=1 -o test-5.html
*/

const char* file_url = "http://localhost:9999/ball";

void onLoadData(void* user_data, void* buffer, int size_in_bytes) {
    cout << (const char *)buffer << endl;
    cout << "on load data" << endl;
    if (size_in_bytes)
        exit(1);
}

void onErrorData(void*){
    cout << "on error data" << endl;
    exit(1);
}

void wait() {
    emscripten_async_wget_data(file_url, nullptr, onLoadData, onErrorData);
    cout << "wait" << endl;
}

void onLoad(const char * str) {
    cout << "onLoad: " << endl << str << endl;
}

void onError(const char * str) {
    cout << "onError: " << endl << str << endl;
}

int main(int argc, char* argv[]) {
    try {
//        vector<uint8_t> data;
//        unsigned w, h;
//        unsigned error = lodepng::decode(data, w, h, "data/ball.png", LCT_RGBA);
//        cout << "error " << error << ", w = " << w << ", h = " << h << endl;

        cout << "1" << endl;
        emscripten_async_wget(file_url, "/tmp/ball.png", onLoad, onError);
        emscripten_set_main_loop(wait, 0, 0);
        cout << "2" << endl;

//        emscripten_wget("http://localhost:9999/test_file", "/test_file");

        return 0;
    } catch (exception const & e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}


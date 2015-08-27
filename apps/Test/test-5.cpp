/*
 * test-4.cpp
 *
 *  Created on: 24 авг. 2015 г.
 *      Author: Pavel
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <emscripten/emscripten.h>

#include "lodepng.h"

using namespace std;

class LoadFile {
public:
    LoadFile(const std::string& url, const std::string& file) :
        m_url(url), m_file(file) {
        emscripten_async_wget2(url.c_str(), file.c_str(), "GET", "", this, onload_func, onerror_func, onprogress_func);
    }
    ~LoadFile() {
    }

private:
    // emscripten_async_wget2
    static void onload_func(unsigned arg0, void* userData, const char* file) {
        auto self = static_cast<LoadFile*>(userData);

        vector<uint8_t> data;
        unsigned w, h;
        unsigned error = lodepng::decode(data, w, h, file, LCT_RGBA);
        cout << "error " << error << ", w = " << w << ", h = " << h << endl;
    }
    static void onerror_func(unsigned arg0, void* userData, int http_status_code) {
        cout << "on error: " << http_status_code << endl;
    }
    static void onprogress_func(unsigned arg0, void* userData, int completeInPersent) {
    }

    string m_url, m_file;
};

class LoadData {
public:
    LoadData(const std::string& url){
        emscripten_async_wget2_data(url.c_str(), "GET", "", this, 1, data_onload_func, data_onerror_func,
            data_onprogress_func);
    }
    virtual ~LoadData(){
    }

private:
    // emscripten_async_wget2_data
    static void data_onload_func(unsigned arg0, void* userData, void* buffer, unsigned sizeInBytes) {
        auto self = static_cast<LoadFile*>(userData);

        vector<uint8_t> in{static_cast<uint8_t*>(buffer), static_cast<uint8_t*>(buffer) + sizeInBytes};

        lodepng::State s;
        vector<uint8_t> data;
        unsigned w, h;
        unsigned error = lodepng::decode(data, w, h, s, in);
        cout << "error " << error << ", w = " << w << ", h = " << h << endl;
    }
    static void data_onerror_func(unsigned, void* userData, int errorCode, const char* statusDescription) {
        cout << "on data error " << errorCode << " " << statusDescription << endl;
    }
    static void data_onprogress_func(unsigned, void* userData, int bytesLoaded, int totalSizeInBytes) {
    }
};

const char* file_url = "http://127.0.0.1:9999/ball";

int main(int argc, char* argv[]) {
    try {

        LoadData memFile("http://127.0.0.1:9999/ball");
        LoadFile loadFile("http://127.0.0.1:9999/ball", "/tmp/ball.png");

        return 0;
    } catch (exception const & e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}


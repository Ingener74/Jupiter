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

//#include "lodepng.h"

using namespace std;

class LoadFile {
public:
    LoadFile(const std::string& url, const std::string& file) :
        m_url(url), m_file(file) {
//        emscripten_async_wget(url.c_str(), file.c_str(), onLoad, onError);

        emscripten_async_wget2(url.c_str(), file.c_str(), "GET", nullptr, this, )
    }
    ~LoadFile() {
    }
    const std::string& getFile() const {
        return m_file;
    }
    const std::string& getUrl() const {
        return m_url;
    }

private:
    static void onload_func(unsigned arg0, void* user_data, const char* file) {
        emscripten_async_wget2_data();
    }
    static void onerror_func(unsigned arg0, void* user_data, int http_status_code) {
    }
    static void onprogress_func(unsigned arg0, void* user_data, int complete_persentage) {
    }

//    static void onLoad(const char * str) {
//        emscripten_async_wget_data(str, this, onLoadData, onErrorData);
//    }
//    static void onError(const char * str) {
//        throw runtime_error("on error " + string{str});
//    }
//    static void onLoadData(void* user_data, void* buffer, int size_in_bytes) {
//        auto self = static_cast<LoadFile*>(user_data);
//        ofstream file;
//        file.open(self->getFile().c_str());
//        file.write(static_cast<const char*>(buffer), size_in_bytes);
//        file.flush();
//        file.close();
//
//        cout << "size " << size_in_bytes << endl;
//    }
//    static void onErrorData(void*){
//        throw runtime_error("on error data");
//    }

    std::string m_url, m_file;
};

/*
em++ ../../../apps/Test/test-5.cpp -s ASYNCIFY=1 -o test-5.html
*/

const char* file_url = "http://127.0.0.1:9999/ball";

//void onLoadData(void* user_data, void* buffer, int size_in_bytes) {
//    cout << (const char *)buffer << endl;
//    cout << "on load data " << size_in_bytes << endl;
//    if (size_in_bytes)
//        exit(1);
//}
//
//void onErrorData(void*){
//    cout << "on error data" << endl;
//    exit(1);
//}
//
//void wait() {
////    emscripten_async_wget_data(file_url, nullptr, onLoadData, onErrorData);
////    cout << "wait" << endl;
//}
//
//void onLoad(const char * str) {
//    cout << "onLoad: " << endl << str << endl;
//
//    emscripten_async_wget_data(file_url, nullptr, onLoadData, onErrorData);
//}
//
//void onError(const char * str) {
//    cout << "onError: " << endl << str << endl;
//}

int main(int argc, char* argv[]) {
    try {
//        vector<uint8_t> data;
//        unsigned w, h;
//        unsigned error = lodepng::decode(data, w, h, "data/ball.png", LCT_RGBA);
//        cout << "error " << error << ", w = " << w << ", h = " << h << endl;

//        emscripten_async_wget(file_url, "/tmp/ball.png", onLoad, onError);
//        emscripten_set_main_loop(wait, 0, 0);
//        emscripten_wget("http://localhost:9999/test_file", "/test_file");

        LoadFile loadFile("http://127.0.0.1:9999/ball", "/tmp/ball.png");

        return 0;
    } catch (exception const & e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}


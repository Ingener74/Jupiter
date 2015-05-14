/*
 * LinuxFileFactory.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include <stdio.h>

#include <vector>
#include <iostream>
#include <memory>

#include "Jupiter/Tools.h"
#include "Jupiter/FileFactory.h"

namespace jupiter {

using namespace std;

class FileBuffer: public Buffer {
public:
    FileBuffer(const string& fileName) :
        fileName(fileName) {
        shared_ptr<FILE> f(fopen(fileName.c_str(), "rb"), [](FILE* df)
        {
            if(df)
            fclose(df);
        });
        jassert(f, "can't open file " + fileName);

        fseek(f.get(), 0, SEEK_END);
        auto size = ftell(f.get());
        rewind(f.get());

        buffer.resize(size);

        char*
        ptr = reinterpret_cast<char*>(buffer.data());

        auto res = fread(ptr, sizeof(char), size, f.get());
        jassert(res == size, "can't read file");

        ptr = reinterpret_cast<char*>(buffer.data());
        setg(ptr, ptr, ptr + buffer.capacity());
    }
    virtual ~FileBuffer() {
        cout << __FUNCTION__ << ": " << fileName << endl;
    }

private:
    string fileName;
};

std::unique_ptr<Buffer> FileFactory::create(const string& fileName) {
    return make_unique_<FileBuffer>(fileName);
}

} /* namespace jupiter */

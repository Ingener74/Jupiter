/*
 * LinuxFileFactory.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "Jupiter/Tools.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/LinuxFileFactory.h"

namespace jupiter {

using namespace std;

class FileBuffer: public streambuf {
public:
    FileBuffer(const string& fileName) :
        _fileName(fileName) {
        shared_ptr<FILE> f(fopen(_fileName.c_str(), "rb"), [](FILE* df)
        {
            if(df)
            fclose(df);
        });
        if (!f)
            throw JupiterError("can't open file " + _fileName);

        fseek(f.get(), 0, SEEK_END);
        auto size = ftell(f.get());
        rewind(f.get());

        _buffer.reserve(size);

        auto res = fread(_buffer.data(), sizeof(char), size, f.get());
        if (res != size)
            throw JupiterError("can't read file");

        setg(_buffer.data(), _buffer.data(), _buffer.data() + _buffer.capacity());
    }
    virtual ~FileBuffer() {
        cout << __PRETTY_FUNCTION__ << ": " << _fileName << endl;
    }

private:
    string _fileName;
    vector<char> _buffer;
};

unique_ptr<streambuf> LinuxFileFactory::create(const string& fileName) {
    return make_unique_<FileBuffer>(fileName);
}

} /* namespace jupiter */

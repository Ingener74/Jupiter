/*
 * FileResource.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: pavel
 */

#include <Jupiter/FileResource.h>
#include <Jupiter/JupiterError.h>

#include <string>
#include <memory>
#include <iostream>

using namespace std;

namespace jupiter
{

FileResource::FileResource()
{
}

FileResource::~FileResource()
{
}

/*
 * FileBuffer
 */
class FileBuffer: public basic_streambuf<char>
{
public:
    FileBuffer(const string& fileName)
    {
        auto file = fopen(fileName.c_str(), "rb");
        fseek(file, 0, SEEK_END);
        auto size = ftell(file);
        rewind(file);

        _buffer.reserve(size);

        auto res = fread(_buffer.data(), sizeof(char), size, file);
        if(res != size)
            throw JupiterError("can't read file");
        fclose(file);

//        cout << string(_buffer.data()) << endl;

        setg(_buffer.data(), _buffer.data(), _buffer.data() + _buffer.size());
    }
    virtual ~FileBuffer() = default;

private:
    vector<char> _buffer;
};

ResourceManager::Resource FileResource::createResource(const string& fileName)
{
    return make_shared<istream>(new FileBuffer(fileName));
}

} /* namespace jupiter */

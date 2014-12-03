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

/*
 * FileBuffer
 */
class FileBuffer: public streambuf
{
public:
    FileBuffer(const string& fileName)
    {
        auto file = fopen(fileName.c_str(), "rb");
        if (!file) throw JupiterError("can't open file " + fileName);
        fseek(file, 0, SEEK_END);
        auto size = ftell(file);
        rewind(file);

        _buffer.reserve(size);

        auto res = fread(_buffer.data(), sizeof(char), size, file);
        if (res != size) throw JupiterError("can't read file");
        fclose(file);

        setg(_buffer.data(), _buffer.data(), _buffer.data() + _buffer.capacity());
    }
    virtual ~FileBuffer() // = default;
    {
        // FIXME dtor not called
        cout << __PRETTY_FUNCTION__ << endl;
    }

private:
    vector<char> _buffer;
};

ResourceManager::Resource FileResource::createResource(const string& fileName)
{
    auto tmp = new istream(new FileBuffer(fileName));
//    cout << __PRETTY_FUNCTION__ << " " << static_cast<void*>(tmp) << endl;
    ResourceManager::Resource t(tmp, [](istream* d)
    {
        delete d->rdbuf();
//        cout << __PRETTY_FUNCTION__ << " " << static_cast<void*>(d) << endl;
    });
    return t;

//    return make_shared<istream>(new FileBuffer(fileName));
}

} /* namespace jupiter */

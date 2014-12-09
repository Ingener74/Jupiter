/*
 * FileResource.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: pavel
 */

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include <Jupiter/FileResource.h>
#include <Jupiter/JupiterError.h>

using namespace std;

namespace jupiter
{

/*
 * FileBuffer
 */
class FileBuffer: public streambuf
{
public:
    FileBuffer(const string& fileName): _fileName(fileName)
    {
        shared_ptr<FILE> f(fopen(_fileName.c_str(), "rb"), [](FILE* df)
        {
            if(df)
                fclose(df);
        });
        if (!f) throw JupiterError("can't open file " + _fileName);

        fseek(f.get(), 0, SEEK_END);
        auto size = ftell(f.get());
        rewind(f.get());

        _buffer.reserve(size);

        auto res = fread(_buffer.data(), sizeof(char), size, f.get());
        if (res != size) throw JupiterError("can't read file");

        setg(_buffer.data(), _buffer.data(), _buffer.data() + _buffer.capacity());
    }
    virtual ~FileBuffer() // = default;
    {
        cout << __PRETTY_FUNCTION__ << " " << _fileName << endl;
    }

private:
    string _fileName;
    vector<char> _buffer;
};

ResourceManager::Resource FileResource::createResource(const string& fileName)
{
    auto tmp = new istream(new FileBuffer(fileName));
    ResourceManager::Resource t(tmp, [](istream* d)
    {
        delete d->rdbuf();
        delete d;
    });
    return t;
//    return make_shared<istream>(new FileBuffer(fileName));
}

} /* namespace jupiter */

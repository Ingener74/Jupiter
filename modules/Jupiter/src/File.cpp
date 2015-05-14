/*
 * File.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include "Jupiter/File.h"

namespace jupiter {

using namespace std;

const vector<uint8_t>& Buffer::getBuffer() const {
    return buffer;
}

File::File(const string& fileName) :
    _buffer(_factory ? _factory->create(_base + (_base.empty() ? "" : "/") + fileName) :
            throw JupiterError("have no file buffer factory")), _i(_buffer.get()) {
}

istream& File::getStream() {
    return _i;
}

const vector<uint8_t>& File::getBuffer() const {
    return _buffer->getBuffer();
}

void File::setBase(const string& base) {
    _base = base;
}

void File::setBufferFactory(BufferFactory* factory) {
    _factory = move(factory);
}

}  // namespace jupiter


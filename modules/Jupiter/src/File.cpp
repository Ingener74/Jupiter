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
    buffer(factory ? factory->create(base + (base.empty() ? "" : "/") + fileName) :
            throw JupiterError("have no file buffer factory")), i(buffer.get()) {
}

istream& File::getStream() {
    return i;
}

const vector<uint8_t>& File::getBuffer() const {
    return buffer->getBuffer();
}

void File::setBase(const string& base) {
    File::base = base;
}

void File::setBufferFactory(BufferFactory* factory) {
    File::factory = move(factory);
}

}  // namespace jupiter


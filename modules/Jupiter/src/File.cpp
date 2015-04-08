/*
 * File.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include "Jupiter/File.h"

namespace jupiter {

using namespace std;

File::File(const std::string& fileName) :
    buffer(factory ? factory->create(base + (base.empty() ? "" : "/") + fileName) :
            throw JupiterError("have no file buffer factory")), i(buffer.get()) {
}

std::istream& File::getStream() {
    return i;
}

std::vector<uint8_t> File::getBuffer() {
    return {};
}

void File::setBase(const std::string& base) {
    File::base = base;
}

void File::setBufferFactory(BufferFactory* factory) {
    File::factory = std::move(factory);
}

}  // namespace jupiter

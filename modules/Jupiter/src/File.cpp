/*
 * File.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#include "Jupiter/JupiterError.h"
#include "Jupiter/File.h"

namespace jupiter {

BufferFactory* File::factory = nullptr;
std::string File::base = "";

File::File(const std::string& fileName) :
    buffer(factory ? factory->create(base + "/" + fileName) : throw JupiterError("have no file buffer factory")), i(
        buffer) {
}

File::~File() {
    if (buffer)
        delete buffer;
}

std::istream& File::file() {
    return i;
}

void File::setBufferFactory(BufferFactory* factory) {
    if (File::factory)
        delete File::factory;
    File::factory = factory;
}

void File::setBase(const std::string& base) {
    File::base = base;
}

}  // namespace jupiter

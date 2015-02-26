/*
 * File.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_

#include <iostream>

#include "Jupiter/Aware.h"

namespace jupiter {

class BufferFactory {
public:
    virtual ~BufferFactory() = default;
    virtual std::streambuf* create(const std::string& fileName) = 0;
};

class File{
public:
    File(const std::string& fileName);
    virtual ~File();

    std::istream& file();

    static void setBufferFactory(BufferFactory* = nullptr);
    static void setBase(const std::string& base);

private:
    std::streambuf* buffer = nullptr;
    std::istream i;

    static BufferFactory* factory;
    static std::string base;
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_ */

/*
 * File.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_

#include <iostream>
#include <memory>

#include "Jupiter/JupiterError.h"

namespace jupiter {

class BufferFactory {
public:
    virtual ~BufferFactory() = default;
    virtual std::unique_ptr<std::streambuf> create(const std::string& fileName) = 0;
};

class File {
public:
    File(const std::string& fileName);
    virtual ~File() = default;

    std::istream& stream();

    static void setBufferFactory(std::unique_ptr<BufferFactory> factory = nullptr);
    static void setBase(const std::string& base);

private:
    std::unique_ptr<std::streambuf> buffer;
    std::istream i;

    static std::unique_ptr<BufferFactory> factory;
    static std::string base;
};

inline File::File(const std::string& fileName) :
    buffer(factory ? factory->create(base + (base.empty() ? "" : "/") + fileName) :
            throw JupiterError("have no file buffer factory")), i(buffer.get()) {
}

inline std::istream& File::stream() {
    return i;
}

inline void File::setBase(const std::string& base) {
    File::base = base;
}

inline void File::setBufferFactory(std::unique_ptr<BufferFactory> factory) {
    File::factory = std::move(factory);
}

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_ */

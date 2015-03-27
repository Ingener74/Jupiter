/*
 * File.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_

#ifdef SWIG
    namespace jupiter {
        %ignore BufferFactory::create(const std::string& fileName);
    }  // namespace jupiter
#else
    #include <iostream>
    #include <memory>

#endif

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

    /*
    const void* getBuffer() const;
    const uint32_t getSize() const;
    */

    static void setBufferFactory(BufferFactory* factory = nullptr);
    static void setBase(const std::string& base);

private:
    std::unique_ptr<std::streambuf> buffer;
    std::istream i;

    static BufferFactory* factory;
    static std::string base;
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_ */

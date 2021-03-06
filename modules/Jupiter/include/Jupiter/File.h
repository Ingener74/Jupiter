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
        %ignore /*jupiter::*/BufferFactory::create(const std::string& fileName);
    }  // namespace jupiter
#else
    #include <iostream>
    #include <memory>
    #include <vector>
#endif

#include "RCO.h"
#include "JupiterError.h"

namespace jupiter {

class Buffer: public std::streambuf {
public:
    virtual ~Buffer() = default;

    const std::vector<uint8_t>& getBuffer() const;

protected:
    std::vector<uint8_t> buffer;
};

class BufferFactory {
public:
    virtual ~BufferFactory() = default;
    virtual std::unique_ptr<Buffer> create(const std::string& fileName) = 0;
};

class File: virtual public RCO {
public:
    File(const std::string& fileName);
    virtual ~File() = default;

    std::istream& getStream();
    const std::vector<uint8_t>& getBuffer() const;

    static void setBufferFactory(BufferFactory* factory = nullptr);
    static void setBase(const std::string& base);

private:
    std::unique_ptr<Buffer> _buffer;
    std::istream _i;

    static BufferFactory* _factory;
    static std::string _base;
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_FILE_H_ */

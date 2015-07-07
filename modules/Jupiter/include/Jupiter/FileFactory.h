/*
 * LinuxFileFactory.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_LINUXFILEFACTORY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_LINUXFILEFACTORY_H_

#include "File.h"

namespace jupiter {

class FileFactory : public BufferFactory {
public:
    FileFactory() = default;
    virtual ~FileFactory() = default;

    virtual std::unique_ptr<Buffer> create(const std::string& fileName);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_LINUXFILEFACTORY_H_ */

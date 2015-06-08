/*
 * FileShader.h
 *
 *  Created on: 19 марта 2015 г.
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_FILESHADER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_FILESHADER_H_

#include "Shader.h"

namespace jupiter {

class File;

class FileShader: public Shader {
public:
    FileShader(File* vertex, File* fragment);
    virtual ~FileShader();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_FILESHADER_H_ */

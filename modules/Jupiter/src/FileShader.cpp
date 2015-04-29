/*
 * FileShader.cpp
 *
 *  Created on: 19 марта 2015 г.
 *      Author: pavel
 */

#include <iterator>
#include "Jupiter/File.h"
#include "Jupiter/FileShader.h"

namespace jupiter {

using namespace std;

FileShader::FileShader(File* vertex, File* fragment) throw (JupiterError) {
    if (!vertex)
        throw JupiterError("bad vertex file");
    if (!fragment)
        throw JupiterError("bad fragment file");

    string vertexShaderSource { (istreambuf_iterator<char>(vertex->getStream())), istreambuf_iterator<char>() };
    string fragmentShaderSource { (istreambuf_iterator<char>(fragment->getStream())), istreambuf_iterator<char>() };

    _program = createProgram(vertexShaderSource, fragmentShaderSource);
}

FileShader::~FileShader() {
    glDeleteProgram(_program);
}

} /* namespace jupiter */

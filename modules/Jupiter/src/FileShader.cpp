/*
 * FileShader.cpp
 *
 *  Created on: 19 марта 2015 г.
 *      Author: pavel
 */

#include <iterator>

#include "Jupiter/Ref.h"
#include "Jupiter/File.h"
#include "Jupiter/FileShader.h"

namespace jupiter {

using namespace std;

FileShader::FileShader(File* vertex, File* fragment) {
    Ref<File> { vertex };
    Ref<File> { fragment };

    jassert(vertex, "bad vertex file");
    jassert(fragment, "bad fragment file");

    string vertexShaderSource { (istreambuf_iterator<char>(vertex->getStream())), istreambuf_iterator<char>() };
    string fragmentShaderSource { (istreambuf_iterator<char>(fragment->getStream())), istreambuf_iterator<char>() };

    _program = createProgram(vertexShaderSource, fragmentShaderSource);
}

FileShader::~FileShader() {
    glDeleteProgram(_program);
}

} /* namespace jupiter */

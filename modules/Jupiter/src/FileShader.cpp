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

FileShader::FileShader(File* vertex, File* fragment) {
    if (!vertex)
        throw JupiterError("bad vertex file");
    if (!fragment)
        throw JupiterError("bad fragment file");

    cout << __PRETTY_FUNCTION__ << " 1" << endl;

    string vertexShaderSource { (istreambuf_iterator<char>(vertex->getStream())), istreambuf_iterator<char>() };
    string fragmentShaderSource { (istreambuf_iterator<char>(fragment->getStream())), istreambuf_iterator<char>() };

    cout << __PRETTY_FUNCTION__ << " 2" << endl;

    _program = createProgram(vertexShaderSource, fragmentShaderSource);

    cout << __PRETTY_FUNCTION__ << " 3" << endl;

}

FileShader::~FileShader() {
    glDeleteProgram(_program);
}

} /* namespace jupiter */

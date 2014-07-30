/*
 * SimpleShaderLoader.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef SIMPLESHADERLOADER_H_
#define SIMPLESHADERLOADER_H_

#include <Engine/Common.h>
#include <Engine/IShaderLoader.h>

namespace ndk_game
{

class SimpleShaderLoader: public IShaderLoader
{
public:
    SimpleShaderLoader(const std::string& vertexShader,
            const std::string fragmentShader);
    virtual ~SimpleShaderLoader();

    virtual const char* getVertexShader() const;
    virtual const char* getFragmentShader() const;

private:
    std::string _vs, _fs;
};

} /* namespace ndk_game */

#endif /* SIMPLESHADERLOADER_H_ */

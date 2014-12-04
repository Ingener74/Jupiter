/*
 * IShaderLoader.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef ISHADERLOADER_H_
#define ISHADERLOADER_H_

#include <memory>
#include <string>

namespace jupiter
{

class IShaderLoader
{
public:
    virtual ~IShaderLoader() = default;

    virtual std::string getVertexShader() const = 0;
    virtual std::string getFragmentShader() const = 0;

protected:
    IShaderLoader() = default;
};

} /* namespace ndk_game */

#endif /* ISHADERLOADER_H_ */

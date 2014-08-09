/*
 * IShaderLoader.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef ISHADERLOADER_H_
#define ISHADERLOADER_H_

#include <Jupiter/Common.h>

namespace jupiter
{

class IShaderLoader
{
public:
    using Ptr = std::shared_ptr<IShaderLoader>;

    virtual ~IShaderLoader()
    {
    }

    virtual std::string getVertexShader() const = 0;
    virtual std::string getFragmentShader() const = 0;

protected:
    IShaderLoader()
    {
    }
};

} /* namespace ndk_game */

#endif /* ISHADERLOADER_H_ */

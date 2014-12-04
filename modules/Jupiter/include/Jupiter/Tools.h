/*
 * Tools.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <memory>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

class Tools
{
public:
    using Ptr = std::shared_ptr<Tools>;

    static Tools::Ptr instance();
    virtual ~Tools() = default;

    static void glError() throw (JupiterError);

private:
    Tools() = default;
};

} /* namespace ndk_game */

#endif /* TOOLS_H_ */

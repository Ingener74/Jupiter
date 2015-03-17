/*
 * Tools.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <memory>
#include <utility>
#include "Jupiter/JupiterError.h"

namespace jupiter
{

template <typename T, typename ... Args>
std::unique_ptr<T> make_unique_( Args ... args )
{
    std::unique_ptr<T> ptr(new T(std::forward<Args>(args)...));
    return ptr;
}

class Tools
{
public:
    Tools() = delete;
    virtual ~Tools() = delete;

    static void glError() throw (JupiterError);
};

} /* namespace ndk_game */

#endif /* TOOLS_H_ */

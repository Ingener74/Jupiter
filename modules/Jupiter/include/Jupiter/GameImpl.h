/*
 * GameImpl.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_GAMEIMPL_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_GAMEIMPL_H_

#include <Jupiter/Node.h>

namespace jupiter
{

class GameImpl
{
public:
    GameImpl(Node, int32_t width, int32_t height);
    virtual ~GameImpl();

    Node& getRootNode();
    int32_t getWidth() const;
    int32_t getHeight() const;

private:
    Node node;
    int32_t width, height;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAMEIMPL_H_ */

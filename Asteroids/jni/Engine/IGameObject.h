/*
 * IGameObject.h
 *
 *  Created on: May 30, 2014
 *      Author: pavel
 */

#ifndef IGAMEOBJECT_H_
#define IGAMEOBJECT_H_

#include <Engine/Common.h>
#include <Engine/Sprite.h>

namespace ndk_game
{

class IGameObject
{
public:
    using Ptr = std::shared_ptr<IGameObject>;

    virtual ~IGameObject()
    {
    }

    virtual void update(double elapsed) throw (std::runtime_error) = 0;
    virtual void input(int x, int y) throw (std::runtime_error) = 0;
    virtual std::list<Sprite::Ptr> getSprites() const throw () = 0;
    virtual std::string getName() const throw () = 0;

protected:
    IGameObject()
    {
    }
};

} /* namespace ndk_game */

#endif /* IGAMEOBJECT_H_ */

/*
 * IGameObject.h
 *
 *  Created on: May 30, 2014
 *      Author: pavel
 */

#ifndef IGAMEOBJECT_H_
#define IGAMEOBJECT_H_

#include <Jupiter/Common.h>
#include <Jupiter/Sprite.h>

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
    virtual std::list<Sprite::Ptr> getSprites() const throw () = 0;
    virtual std::string getName() const throw () = 0;

    virtual void input(int x, int y) throw (std::runtime_error)
    {
    }
    virtual void collision(IGameObject::Ptr) throw (std::runtime_error)
    {
    }
    virtual bool removeMe() const throw ()
    {
        return false;
    }

protected:
    IGameObject()
    {
    }
};

} /* namespace ndk_game */

#endif /* IGAMEOBJECT_H_ */

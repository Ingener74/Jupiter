/*
 * IGameObject.h
 *
 *  Created on: May 30, 2014
 *      Author: pavel
 */

#ifndef IGAMEOBJECT_H_
#define IGAMEOBJECT_H_

#include <list>
#include <memory>
#include <string>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

class Sprite;

class IGameObject
{
public:
    virtual ~IGameObject()
    {
    }

    virtual void update(double elapsed) throw (JupiterError) = 0;
    virtual std::list<std::shared_ptr<Sprite>> getSprites() const throw () = 0;
    virtual std::string getName() const throw () = 0;

    virtual void input(int x, int y) throw (JupiterError)
    {
    }
    virtual void collision(std::shared_ptr<IGameObject>) throw (JupiterError)
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

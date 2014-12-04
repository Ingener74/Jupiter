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
    virtual ~IGameObject() = default;

    virtual void update(double elapsed) = 0;
    virtual std::list<std::shared_ptr<Sprite>> getSprites() const = 0;
    virtual std::string getName() const = 0;

    virtual void input(int x, int y)
    {
    }
    virtual void collision(std::shared_ptr<IGameObject>)
    {
    }
    virtual bool removeMe() const
    {
        return false;
    }

protected:
    IGameObject() = default;
};

} /* namespace ndk_game */

#endif /* IGAMEOBJECT_H_ */

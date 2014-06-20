/*
 * IDrawEngine.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef IDRAWENGINE_H_
#define IDRAWENGINE_H_

#include <Engine/Common.h>
#include <Engine/Scene.h>

namespace ndk_game
{

class IDrawEngine
{
public:
    using Ptr = std::shared_ptr<IDrawEngine>;

    virtual ~IDrawEngine()
    {
    }

    virtual void setCurrentScene(Scene::Ptr) throw () = 0;
    virtual void draw() throw (std::runtime_error) = 0;
    virtual void inputToAll(int x, int y) throw ()= 0;
    virtual void animateAll(double elapsedMs) throw (std::runtime_error) = 0;

protected:
    IDrawEngine()
    {
    }
};

} /* namespace ndk_game */

#endif /* IDRAWENGINE_H_ */

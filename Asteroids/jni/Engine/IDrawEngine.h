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

    virtual void draw(Scene::Ptr) throw (std::runtime_error) = 0;

protected:
    IDrawEngine()
    {
    }
};

} /* namespace ndk_game */

#endif /* IDRAWENGINE_H_ */

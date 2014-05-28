/*
 * Scene.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <Engine/Common.h>

namespace ndk_game
{

class Scene
{
public:
    using Ptr = std::shared_ptr<Scene>;

    Scene();
    virtual ~Scene();
};

} /* namespace ndk_game */

#endif /* SCENE_H_ */

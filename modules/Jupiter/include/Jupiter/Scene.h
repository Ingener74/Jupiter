/*
 * Scene.h
 *
 *  Created on: May 28, 2014
 *      Author: ingener
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include <memory>

namespace jupiter
{

class IGameObject;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    std::list<std::shared_ptr<IGameObject>> gameObject;
};

} /* namespace ndk_game */

#endif /* SCENE_H_ */

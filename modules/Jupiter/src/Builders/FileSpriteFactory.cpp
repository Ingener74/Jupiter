/*
 * FileSpriteFactory.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#include <memory>

#include <glm/glm.hpp>

#include <Jupiter/FileSpriteFactory.h>
#include <Jupiter/JupiterError.h>
#include <Jupiter/Texture.h>
#include <Jupiter/Shape.h>
#include "../SpriteImpl.h"

namespace jupiter
{

using namespace std;

FileSpriteFactory::FileSpriteFactory()
{
}

FileSpriteFactory::~FileSpriteFactory()
{
}

std::shared_ptr<SpriteImpl> FileSpriteFactory::create(const std::string& spriteId)
{
//    throw JupiterError{"i can't now build sprite impl"};

    Texture   t{spriteId};
    Shape     s{};

    return make_shared<SpriteImpl>(t, s);
}

} /* namespace jupiter */

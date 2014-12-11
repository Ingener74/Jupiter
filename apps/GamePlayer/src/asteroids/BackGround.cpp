/*
 * BackGround.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: pavel
 */

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BackGround.h"

using namespace std;
using namespace glm;
using namespace jupiter;

BackGround::BackGround()//: background("resources/images/bg.png")
{
    auto textureLoader = make_shared<FileTextureLoader>("resources/images/bg.png");

    auto texture = Texture::create(textureLoader);
    auto rect = make_shared<RectSpriteLoader>(800, 800, 0, 0, 1, 0, 1);

    background = make_shared<Sprite>(texture, rect);
}

void BackGround::update(double elapsed)
{
//    auto m = background->getModelMatrix();
//    background->setModelMatrix(translate(m, vec3{0.01, 0, 0}));
}

list<shared_ptr<Sprite> > BackGround::getSprites() const
{
    return {background};
}

string BackGround::getName() const
{
    return "Background";
}

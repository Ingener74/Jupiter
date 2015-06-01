/*
 * Jupiter.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef JUPITER_H_
#define JUPITER_H_

#include "Jupiter/JupiterError.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Game.h"
#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/Controller.h"
#include "Jupiter/Image.h"
#include "Jupiter/Texture.h"
#include "Jupiter/File.h"

#include "Jupiter/FileFactory.h"

#include "Jupiter/PngImage.h"

#include "Jupiter/ImageTexture.h"

#include "Jupiter/Shader.h"
#include "Jupiter/FileShader.h"

#include "Jupiter/Shape.h"
#include "Jupiter/ImageShape.h"

//#include "Jupiter/JsonGame.h"

#include "Jupiter/Camera.h"

#include "Jupiter/NodeVisitor.h"
#include "Jupiter/RenderVisitor.h"
#include "Jupiter/PrintVisitor.h"

#include "Jupiter/Box2dVisitor.h"
#include "Jupiter/Box2dNode.h"

#include "Jupiter/MoveListener.h"
#include "Jupiter/ScaleListener.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/RotationListener.h"
#include "Jupiter/KeyboardListener.h"

#include "Jupiter/SpriteBox2d.h"

namespace jupiter {


template<typename T>
T* node2(Node* t) {
    auto r = dynamic_cast<T*>(t);
    jassert(r, "can't cast node");
    return r;
}

#ifdef SWIG

    %template(node2Sprite)        node2<Sprite>;
    %template(node2SpriteBox2d)   node2<SpriteBox2d>;
    %template(node2Box2dNode)     node2<Box2dNode>;
    %template(node2Camera)        node2<Camera>;

#endif

void startJupiter();
void endJupiter();

}  // namespace jupiter

#endif /* JUPITER_H_ */

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
#include "Jupiter/Sprite.h"
#include "Jupiter/Image.h"
#include "Jupiter/Texture.h"
#include "Jupiter/File.h"

#include "Jupiter/Node.h"
#include "Jupiter/Transform.h"

#include "Jupiter/FileFactory.h"

#include "Jupiter/PngImage.h"

#include "Jupiter/ImageTexture.h"

#include "Jupiter/Shader.h"
#include "Jupiter/FileShader.h"

#include "Jupiter/Shape.h"
#include "Jupiter/ImageShape.h"

#include "Jupiter/Camera.h"

#include "Jupiter/NodeVisitor.h"
#include "Jupiter/RenderVisitor.h"
#include "Jupiter/PrintVisitor.h"

#include "Jupiter/Physics.h"
#include "Jupiter/Body.h"

#include "Jupiter/MoveListener.h"
#include "Jupiter/ScaleListener.h"
#include "Jupiter/CollisionListener.h"
#include "Jupiter/RotationListener.h"
#include "Jupiter/KeyboardListener.h"

#include "Jupiter/VisualBody.h"

#include "Jupiter/MoveAnimation.h"

#include "Jupiter/PoligonShape.h"
#include "Jupiter/CircleShape.h"
#include "Jupiter/ComplexShape.h"

#include "Jupiter/PhysicsBodyEditorAtlas.h"

#include "Jupiter/RevoluteJoint.h"
#include "Jupiter/DistanceJoint.h"
#include "Jupiter/RopeJoint.h"
#include "Jupiter/MotorJoint.h"
#include "Jupiter/GearJoint.h"
#include "Jupiter/WheelJoint.h"
#include "Jupiter/FrictionJoint.h"
#include "Jupiter/MouseJoint.h"
#include "Jupiter/PrismaticJoint.h"
#include "Jupiter/PulleyJoint.h"
#include "Jupiter/WeldJoint.h"

#ifdef SWIG
#else
    #include "Jupiter/Ref.h"
#endif

namespace jupiter {

template<typename T>
T* node2(Node* t) {
    auto r = dynamic_cast<T*>(t);
    jassert(r, "can't cast node");
    return r;
}

#ifdef SWIG

    %template(node2Sprite)          node2<Sprite>;
    %template(node2Body)            node2<Body>;
    %template(node2Camera)          node2<Camera>;

    %template(node2Joint)           node2<Joint>;
    %template(node2RevoluteJoint)   node2<RevoluteJoint>;
    %template(node2DistanceJoint)   node2<DistanceJoint>;
    %template(node2RopeJoint)       node2<RopeJoint>;
    %template(node2MotorJoint)      node2<MotorJoint>;
    %template(node2GearJoint)       node2<GearJoint>;
    %template(node2WheelJoint)      node2<WheelJoint>;
    %template(node2FrictionJoint)   node2<FrictionJoint>;
    %template(node2MouseJoint)      node2<MouseJoint>;
    %template(node2PrismaticJoint)  node2<PrismaticJoint>;
    %template(node2PulleyJoint)     node2<PulleyJoint>;
    %template(node2WeldJoint)       node2<WeldJoint>;

#endif

void startJupiter();
void endJupiter();

}  // namespace jupiter

#endif /* JUPITER_H_ */

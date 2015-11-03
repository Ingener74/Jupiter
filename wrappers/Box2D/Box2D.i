
#if defined(SWIGPYTHON)
    %module(directors="1") Box2DPython
#elif defined(SWIGLUA)
    %module(directors="1") Box2DLua
#elif defined(SWIGJAVA)
    %module(directors="1") Box2DJava
#elif defined(SWIGCSHARP)
    %module(directors="1") Box2DCSharp
#else
    #warning no tupemaps
#endif

%begin %{
#include <cmath>
%}

%{
#include <Box2D/Box2D.h>
%}

/*
Отключаем следующие сообщения
Box2D/Common/b2Math.h:80: Warning 509: Overloaded method b2Vec2::operator ()(int32) effectively ignored,
Box2D/Common/b2Math.h:74: Warning 509: as it is shadowed by b2Vec2::operator ()(int32) const.
Box2D/Common/b2Math.h:449: Warning 503: Can't wrap 'operator +' unless renamed to a valid identifier.
Box2D/Common/b2Math.h:455: Warning 503: Can't wrap 'operator -' unless renamed to a valid identifier.
Box2D/Common/b2Math.h:460: Warning 503: Can't wrap 'operator *' unless renamed to a valid identifier.
Box2D/Common/b2Math.h:465: Warning 503: Can't wrap 'operator ==' unless renamed to a valid identifier.
Box2D/Common/b2Math.h:482: Warning 503: Can't wrap 'operator *' unless renamed to a valid identifier.
Box2D/Common/b2Math.h:488: Warning 503: Can't wrap 'operator +' unless renamed to a valid identifier.
Box2D/Common/b2Math.h:494: Warning 503: Can't wrap 'operator -' unless renamed to a valid identifier.
Box2D/Common/b2Math.h:511: Warning 503: Can't wrap 'operator +' unless renamed to a valid identifier.
*/
#pragma SWIG nowarn=509,503

/*
b2Body.h:357: Warning 516: Overloaded method b2Body::GetFixtureList() const ignored,
b2Body.h:356: Warning 516: using b2Body::GetFixtureList() instead.
b2Body.h:361: Warning 516: Overloaded method b2Body::GetJointList() const ignored,
b2Body.h:360: Warning 516: using b2Body::GetJointList() instead.
b2Body.h:367: Warning 516: Overloaded method b2Body::GetContactList() const ignored,
b2Body.h:366: Warning 516: using b2Body::GetContactList() instead.
b2Body.h:371: Warning 516: Overloaded method b2Body::GetNext() const ignored,
b2Body.h:370: Warning 516: using b2Body::GetNext() instead.
b2Body.h:381: Warning 516: Overloaded method b2Body::GetWorld() const ignored,
b2Body.h:380: Warning 516: using b2Body::GetWorld() instead.
b2Fixture.h:118: Warning 516: Overloaded method b2Fixture::GetShape() const ignored,
b2Fixture.h:117: Warning 516: using b2Fixture::GetShape() instead.
b2Fixture.h:141: Warning 516: Overloaded method b2Fixture::GetBody() const ignored,
b2Fixture.h:140: Warning 516: using b2Fixture::GetBody() instead.
b2Fixture.h:146: Warning 516: Overloaded method b2Fixture::GetNext() const ignored,
b2Fixture.h:145: Warning 516: using b2Fixture::GetNext() instead.
b2World.h:128: Warning 516: Overloaded method b2World::GetBodyList() const ignored,
b2World.h:127: Warning 516: using b2World::GetBodyList() instead.
b2World.h:134: Warning 516: Overloaded method b2World::GetJointList() const ignored,
b2World.h:133: Warning 516: using b2World::GetJointList() instead.
b2World.h:142: Warning 516: Overloaded method b2World::GetContactList() const ignored,
b2World.h:141: Warning 516: using b2World::GetContactList() instead.
Joints/b2Joint.h:130: Warning 516: Overloaded method b2Joint::GetNext() const ignored,
Joints/b2Joint.h:129: Warning 516: using b2Joint::GetNext() instead.
*/
#pragma SWIG nowarn=516,

%include <Box2D/Common/b2Math.h>
%include <Box2D/Common/b2Settings.h>

%include <Box2D/Collision/Shapes/b2Shape.h>
%include <Box2D/Collision/Shapes/b2CircleShape.h>
%include <Box2D/Collision/Shapes/b2EdgeShape.h>
%include <Box2D/Collision/Shapes/b2ChainShape.h>
%include <Box2D/Collision/Shapes/b2PolygonShape.h>

%include <Box2D/Dynamics/b2Body.h>
%include <Box2D/Dynamics/b2Fixture.h>
%include <Box2D/Dynamics/b2WorldCallbacks.h>
%include <Box2D/Dynamics/b2TimeStep.h>
%include <Box2D/Dynamics/b2World.h>

%include <Box2D/Dynamics/Joints/b2Joint.h>
%include <Box2D/Dynamics/Joints/b2DistanceJoint.h>
%include <Box2D/Dynamics/Joints/b2FrictionJoint.h>
%include <Box2D/Dynamics/Joints/b2GearJoint.h>
%include <Box2D/Dynamics/Joints/b2MotorJoint.h>
%include <Box2D/Dynamics/Joints/b2MouseJoint.h>
%include <Box2D/Dynamics/Joints/b2PrismaticJoint.h>
%include <Box2D/Dynamics/Joints/b2PulleyJoint.h>
%include <Box2D/Dynamics/Joints/b2RevoluteJoint.h>
%include <Box2D/Dynamics/Joints/b2RopeJoint.h>
%include <Box2D/Dynamics/Joints/b2WeldJoint.h>
%include <Box2D/Dynamics/Joints/b2WheelJoint.h>

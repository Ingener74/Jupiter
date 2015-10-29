
#if defined(SWIGPYTHON)
    %module(directors="1") Box2DPython
#elif defined(SWIGLUA)
    %module(directors="1") Box2DLua
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


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

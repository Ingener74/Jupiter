/*
 * Controller.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#include <iostream>

#include <Jupiter/Node.h>
#include <Jupiter/ControllerImpl.h>
#include <Jupiter/Controller.h>

namespace jupiter
{

using namespace std;

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::onVisibleChanged(bool isVisible)
{
//    if(_impl)
//        _impl->onVisibleChanged(isVisible);
}

void Controller::onMove(float x, float y, float z)
{
//    if(_impl)
//        _impl->onMove(x, y, z);
}

void Controller::onPositionChanged(float x, float y, float z)
{
//    if(_impl)
//        _impl->onPositionChanged(x, y, z);
}

void Controller::onScale(float x, float y, float z)
{
//    if(_impl)
//        _impl->onScale(x, y, z);
}

void Controller::onScaleChanged(float x, float y, float z)
{
//    if(_impl)
//        _impl->onScaleChanged(x, y, z);
}

void Controller::onRotate(float x, float y, float z)
{
//    if(_impl)
//        _impl->onRotate(x, y, z);
}

void Controller::onRotationChanged(float x, float y, float z)
{
//    if(_impl)
//        _impl->onRotationChanged(x, y, z);
}

void Controller::update(double elapsedTime)
{
//    if(_impl)
//        _impl->update(elapsedTime);
}

} /* namespace jupiter */


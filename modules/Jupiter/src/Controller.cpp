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
}

void Controller::onMove(float x, float y, float z)
{
}

void Controller::onPositionChanged(float x, float y, float z)
{
}

void Controller::onScale(float x, float y, float z)
{
}

void Controller::onScaleChanged(float x, float y, float z)
{
}

void Controller::onRotate(float x, float y, float z)
{
}

void Controller::onRotationChanged(float x, float y, float z)
{
}

void Controller::update(double elapsedTime)
{
}

} /* namespace jupiter */


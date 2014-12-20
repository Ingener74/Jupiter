/*
 * Controller.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLER_H_

#include <memory>

namespace jupiter
{

class ControllerImpl;

class Controller
{
public:
    Controller();
    Controller(const std::string& controller);
    virtual ~Controller();

    virtual void onVisibleChanged(bool isVisible);
    virtual void onMove(float x, float y, float z);
    virtual void onScaleChanged(float x, float y, float z);
    virtual void onRotate(float x, float y, float z);

    virtual void update(double elapsedTime);

private:
    std::shared_ptr<ControllerImpl> _impl;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLER_H_ */

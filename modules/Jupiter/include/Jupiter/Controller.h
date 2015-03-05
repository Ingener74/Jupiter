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

class Node;

class Controller
{
public:
    Controller();
    virtual ~Controller();

    virtual void onVisibleChanged(bool isVisible);

    virtual void onMove(float x, float y, float z);
    virtual void onPositionChanged(float x, float y, float z);

    virtual void onScale(float x, float y, float z);
    virtual void onScaleChanged(float x, float y, float z);

    virtual void onRotate(float x, float y, float z);
    virtual void onRotationChanged(float x, float y, float z);

    virtual void update(double elapsedTime);

private:
    Node* node = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLER_H_ */

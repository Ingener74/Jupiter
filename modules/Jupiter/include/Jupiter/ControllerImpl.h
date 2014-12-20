/*
 * ControllerImpl.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLERIMPL_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLERIMPL_H_

namespace jupiter
{

class ControllerImpl
{
public:
    ControllerImpl();
    virtual ~ControllerImpl();

    virtual void onVisibleChanged(bool isVisible) = 0;

    virtual void onMove(float x, float y, float z) = 0;
    virtual void onPositionChanged(float x, float y, float z) = 0;

    virtual void onScale(float x, float y, float z) = 0;
    virtual void onScaleChanged(float x, float y, float z) = 0;

    virtual void onRotate(float x, float y, float z) = 0;
    virtual void onRotationChanged(float x, float y, float z) = 0;

    virtual void update(double elapsedTime) = 0;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLERIMPL_H_ */

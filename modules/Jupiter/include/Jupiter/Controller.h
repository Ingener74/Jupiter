/*
 * Controller.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLER_H_

namespace jupiter
{

class Controller
{
public:
    Controller();
    virtual ~Controller();

    virtual void update(double elapsedTime);
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_CONTROLLER_H_ */

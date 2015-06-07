/*
 * Joint.h
 *
 *  Created on: 07 июня 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JOINT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JOINT_H_

#include "Node.h"

namespace jupiter {

class Joint: virtual public Node {
public:
    Joint();
    virtual ~Joint();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JOINT_H_ */

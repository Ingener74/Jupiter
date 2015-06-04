/*
 * Animation.h
 *
 *  Created on: Jun 4, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_ANIMATION_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_ANIMATION_H_

namespace jupiter {

class Node;

class Animation {
public:
    Animation() = default;
    virtual ~Animation() = default;

    virtual void update(float dt) = 0;

    void setNode(Node*);
    Node* getNode();

protected:
    Node* _node = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_ANIMATION_H_ */

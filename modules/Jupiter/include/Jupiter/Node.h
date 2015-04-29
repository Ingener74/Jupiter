/*
 * Node.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_

#ifdef SWIG
    namespace jupiter {
        #pragma SWIG nowarn=341,325
        %ignore Node::NodePtr;
    }  // namespace jupiter
#else
    #include <set>
    #include <list>
    #include <string>

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>

//    #include "Jupiter/Controller.h"
//    #include "Jupiter/JupiterError.h"
#endif

namespace jupiter {

class NodeVisitor;
class Controller;

class Node {
public:
    Node();
    virtual ~Node();

    Node* addNode(Node* node);
    Node* setParent(Node*);
    Node* getParent();

    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;

    Node* setRotation(float x, float y, float z);
    Node* setRotationX(float x);
    Node* setRotationY(float y);
    Node* setRotationZ(float z);

    Node* rotate(float x, float y, float z);
    Node* rotateX(float angle);
    Node* rotateY(float y);
    Node* rotateZ(float z);

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    Node* setPosition(float x, float y, float z);
    Node* setPositionX(float x);
    Node* setPositionY(float y);
    Node* setPositionZ(float z);

    Node* translate(float x, float y, float z);
    Node* translateX(float x);
    Node* translateY(float y);
    Node* translateZ(float z);

    float getScaleX() const;
    float getScaleY() const;

    Node* setScale(float x, float y);
    Node* setScaleX(float x);
    Node* setScaleY(float y);

    Node* scale(float x, float y);
    Node* scaleX(float x);
    Node* scaleY(float y);

    bool isVisible() const;
    Node* setVisible(bool isVisible);

    virtual Node* accept(NodeVisitor* nv);

    Node* setController(Controller* controller);
    Controller* getController();

    const glm::mat4& getModel() const;
    Node* setModel(const glm::mat4& model);

protected:
    bool visible = true;
    glm::mat4 model;
    Controller* controller = nullptr;
    Node* parent = nullptr;
    std::list<Node*> nodes;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */

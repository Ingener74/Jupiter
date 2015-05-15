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
    }
#else
    #include <set>
    #include <list>
    #include <string>

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>
#endif

namespace jupiter {

class NodeVisitor;
class Controller;
class MoveListener;
class ScaleListener;

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

    virtual Node* setRotation(float x, float y, float z);
    Node* setRotationX(float x);
    Node* setRotationY(float y);
    Node* setRotationZ(float z);

    virtual Node* rotate(float x, float y, float z);
    Node* rotateX(float angle);
    Node* rotateY(float y);
    Node* rotateZ(float z);

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    virtual Node* setPosition(float x, float y, float z);
    Node* setPositionX(float x);
    Node* setPositionY(float y);
    Node* setPositionZ(float z);

    virtual Node* translate(float x, float y, float z);
    Node* translateX(float x);
    Node* translateY(float y);
    Node* translateZ(float z);

    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;

    virtual Node* setScale(float x, float y, float z);
    Node* setScale(float scale);
    Node* setScaleX(float x);
    Node* setScaleY(float y);
    Node* setScaleZ(float z);

    virtual Node* scale(float x, float y, float z);
    Node* scale(float s);
    Node* scaleX(float x);
    Node* scaleY(float y);
    Node* scaleZ(float z);

    bool isVisible() const;
    Node* setVisible(bool isVisible);

    virtual Node* accept(NodeVisitor* nv);

    Node* setController(Controller* controller);
    Controller* getController();

    Node* setMoveListener(MoveListener*);
    MoveListener* getMoveListener();

    Node* setScaleListener(ScaleListener* scaleListener);
    ScaleListener* getScaleListener();

    const glm::mat4& getModel() const;
    Node* setModel(const glm::mat4& model);

protected:
    bool               _visible         = true;
    glm::mat4          _model;
    Controller*        _controller      = nullptr;
    Node*              _parent          = nullptr;
    std::list<Node*>   _nodes;
    MoveListener*      _moveListener    = nullptr;
    ScaleListener*     _scaleListener   = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */

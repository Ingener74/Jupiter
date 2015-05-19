/*
 * Node.h
 *
 *  Created on: Dec 13, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_

#ifdef SWIG
    #pragma SWIG nowarn=362
#else
    #include <set>
    #include <list>
    #include <string>

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/quaternion.hpp>
#endif

namespace jupiter {

class NodeVisitor;
class MoveListener;
class ScaleListener;
class RotationListener;

class Node {
public:
    Node();
    virtual ~Node();

    virtual Node* clone(Node*);

    Node* addNode(Node*);
    Node* removeNode(Node*);

    Node* setParent(Node*);
    Node* getParent();

    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;

    virtual Node* setRotation(float x, float y, float z, float angle);
    Node* setRotationX(float angle);
    Node* setRotationY(float angle);
    Node* setRotationZ(float angle);

    virtual Node* rotate(float x, float y, float z, float angle);
    Node* rotateX(float angle);
    Node* rotateY(float angle);
    Node* rotateZ(float angle);

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

    virtual Node* accept(NodeVisitor*);

    Node* setMoveListener(MoveListener*);
    MoveListener* getMoveListener();

    Node* setScaleListener(ScaleListener*);
    ScaleListener* getScaleListener();

    Node* setRotationListener(RotationListener*);
    RotationListener* getRotationListener();

    const glm::mat4& getModel() const;
    Node* setModel(const glm::mat4& model);

protected:
    bool               _visible            = true;

    glm::mat4          _model;
    glm::vec3          _position;
    glm::vec3          _scale              = {1.f, 1.f, 1.f};
    glm::quat          _rotation;

    std::list<Node*>   _nodes;
    Node*              _parent             = nullptr;
    MoveListener*      _moveListener       = nullptr;
    ScaleListener*     _scaleListener      = nullptr;
    RotationListener*  _rotationListener   = nullptr;

    Node(const Node&) = default;
    Node& operator=(const Node&) = default;
    void calcModel();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODE_H_ */

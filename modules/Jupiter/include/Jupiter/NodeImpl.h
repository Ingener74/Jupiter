/*
 * NodeImpl.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_NODEIMPL_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_NODEIMPL_H_

#include <Jupiter/Node.h>

namespace jupiter
{

class NodeImpl
{
public:
    NodeImpl(const std::string& name, bool isVisible, const glm::mat4& model, const Controller&, const std::map<std::string, Node>& nodes);
    virtual ~NodeImpl();

    const std::string& getName()const;

    bool isVisible()const;
    void setVisible(bool);

    const glm::mat4& getModel()const;
    void setModel(const glm::mat4&);

    Controller& getController();
    std::map<std::string, Node>& getNodes();

private:
    std::string _name;
    bool _isVisible = true;
    glm::mat4 _model;
    Controller _controller;
    std::map<std::string, Node> _nodes;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_NODEIMPL_H_ */

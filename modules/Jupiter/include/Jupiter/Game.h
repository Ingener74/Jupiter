/*
 * Game.h
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_

#ifdef SWIG
#else
    #include <list>
    #include <string>

    #include "Ref.h"
#endif

namespace jupiter {

class Node;
class NodeVisitor;
class KeyboardListener;

class Game: virtual public RCO {
public:
    Game() = default;
    virtual ~Game() = default;

    virtual void draw();

    virtual void keyboard(int keyCode);

    virtual int getWidth() const;
    virtual int getHeight() const;

    Game* setHeight(int height = 0);
    Game* setWidth(int width = 0);

    virtual Game* setRootNode(Node*);
    virtual Node* getRootNode();

    virtual Game* setVisitors(const std::list<NodeVisitor*>&);
    virtual const std::list<Ref<NodeVisitor>>& getVisitors() const;

    virtual Game* addVisitor(NodeVisitor*);

    virtual Game* addKeyboardListener(KeyboardListener*);

protected:
    std::list<Ref<NodeVisitor>>        _visitors;
    std::list<Ref<KeyboardListener>>   _keyboardListeners;
    Ref<Node>                          _node;
    int                                _width                = 0;
    int                                _height               = 0;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_ */

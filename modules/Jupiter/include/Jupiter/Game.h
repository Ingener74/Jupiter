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

    #include <string>

#endif

#include "Jupiter/RenderVisitor.h"
#include "Jupiter/Node.h"

namespace jupiter {

class Game {
public:
    Game() = default;
    virtual ~Game() = default;

    virtual void draw();

    virtual void input();

    virtual int getWidth() const;
    virtual int getHeight() const;

    Game* setHeight(int height = 0);
    Game* setWidth(int width = 0);

    virtual Game* setRootNode(Node*);
    virtual Node* getRootNode();

    virtual Game* setVisitors(const std::list<NodeVisitor*>&);
    virtual const std::list<NodeVisitor*>& getVisitors() const;

protected:
    std::list<NodeVisitor*> _visitors;
    Node* _node = nullptr;
    int _width = 0;
    int _height = 0;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_GAME_H_ */

/*
 * GameAgain.h
 *
 *  Created on: Jun 1, 2014
 *      Author: ingener
 */

#ifndef GAMEAGAIN_H_
#define GAMEAGAIN_H_

#include <Jupiter.h>
#include <Tools.h>

class GameAgain: public jupiter::IGameObject
{
public:
    GameAgain(int screenWidth, GameTools, std::function<void()> newGame);
    virtual ~GameAgain();

    virtual void update(double elapsed);
    virtual void input(int x, int y);
    virtual std::list<std::shared_ptr<jupiter::Sprite>> getSprites() const;
    virtual std::string getName() const;

private:
    std::shared_ptr<jupiter::Sprite> _norm, _pushed, _cur;

#ifdef NDK_GAME_DEBUG
    ndk_game::Sprite::Ptr _rect;
#endif

    jupiter::Rect _buttonRect;

    double _fadeOut = 0.0;
    std::function<void()> _newGame;
    GameTools _tools;
};

#endif /* GAMEAGAIN_H_ */

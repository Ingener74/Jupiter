/*
 * ISound.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef ISOUND_H_
#define ISOUND_H_

#include <memory>
#include <Jupiter/JupiterError.h>

namespace jupiter
{

class ISound
{
public:
    virtual ~ISound()
    {
    }

    virtual void play(bool loop = false) = 0;
    virtual void stop() = 0;

protected:
    ISound()
    {
    }
};

} /* namespace ndk_game */

#endif /* ISOUND_H_ */

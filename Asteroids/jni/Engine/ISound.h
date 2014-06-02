/*
 * ISound.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef ISOUND_H_
#define ISOUND_H_

#include <Engine/Common.h>

namespace ndk_game
{

class ISound
{
public:
    using Ptr = std::shared_ptr<ISound>;

    virtual ~ISound()
    {
    }

    virtual void play(bool loop = false) throw (std::runtime_error) = 0;
    virtual void stop() throw () = 0;

protected:
    ISound()
    {
    }
};

} /* namespace ndk_game */

#endif /* ISOUND_H_ */

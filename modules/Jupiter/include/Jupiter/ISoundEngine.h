/*
 * ISoundEngine.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef ISOUNDENGINE_H_
#define ISOUNDENGINE_H_

#include <Jupiter/Common.h>
#include <Jupiter/ISound.h>

namespace ndk_game
{

class ISoundEngine
{
public:
    using Ptr = std::shared_ptr<ISoundEngine>;

    virtual ~ISoundEngine()
    {
    }

    virtual ISound::Ptr loadSound(const std::string& file) = 0;

protected:
    ISoundEngine()
    {
    }
};

} /* namespace ndk_game */

#endif /* ISOUNDENGINE_H_ */

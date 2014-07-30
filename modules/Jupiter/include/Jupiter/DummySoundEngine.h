/*
 * DummySoundEngine.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef DUMMYSOUNDENGINE_H_
#define DUMMYSOUNDENGINE_H_

#include <Engine/ISoundEngine.h>

namespace ndk_game
{

class DummySoundEngine: public ISoundEngine
{
public:
    DummySoundEngine();
    virtual ~DummySoundEngine();

    virtual ISound::Ptr loadSound(const std::string& file);
};

} /* namespace ndk_game */

#endif /* DUMMYSOUNDENGINE_H_ */

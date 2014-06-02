/*
 * SLESSoundEngine.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef SLESSOUNDENGINE_H_
#define SLESSOUNDENGINE_H_

#include <Engine/Common.h>
#include <Engine/ISoundEngine.h>

namespace ndk_game
{

class SLESSound;

class SLESSoundEngine: public ISoundEngine, public std::enable_shared_from_this<SLESSoundEngine>
{
public:
    friend SLESSound;

    SLESSoundEngine(android_app*);
    virtual ~SLESSoundEngine();

    ISound::Ptr loadSound(const std::string& file);

private:
    SLObjectItf _engineObj;
    SLEngineItf _engine;
    SLObjectItf _outMixObj;

    android_app* _app;
};

} /* namespace ndk_game */

#endif /* SLESSOUNDENGINE_H_ */

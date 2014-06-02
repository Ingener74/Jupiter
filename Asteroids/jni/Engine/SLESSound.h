/*
 * SLESSound.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef SLESSOUND_H_
#define SLESSOUND_H_

#include <Engine/Common.h>
#include <Engine/ISound.h>

#include <Engine/SLESSoundEngine.h>

namespace ndk_game
{

class SLESSound: public ISound
{
public:
    SLESSound(android_app*, const std::string& file, std::weak_ptr<SLESSoundEngine> soundEngine);
    virtual ~SLESSound();

    virtual void play(bool loop = false) throw (std::runtime_error);
    virtual void stop() throw ();

private:
    AAssetManager* _assetManager;
    AAsset* _asset;

    std::weak_ptr<SLESSoundEngine> _soundEngine;

    int32_t _descriptor;
    off_t _start;
    off_t _length;

    SLObjectItf _playerObj;
    SLPlayItf _player;
    SLSeekItf _playerSeek;
};

} /* namespace ndk_game */

#endif /* SLESSOUND_H_ */

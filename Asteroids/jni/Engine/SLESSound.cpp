/*
 * SLESSound.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#include <Engine/SLESSound.h>

namespace ndk_game
{

SLESSound::SLESSound(android_app* app, const std::string& file, std::weak_ptr<SLESSoundEngine> soundEngine):
        _assetManager(app->activity->assetManager), _asset(nullptr),
        _soundEngine(soundEngine), _descriptor(0), _start(0), _length(0),
        _playerObj(0), _player(0), _playerSeek(0)
{
    SLresult lRes;

    AAsset* asset = AAssetManager_open(_assetManager, file.c_str(), AASSET_MODE_UNKNOWN);
    if (asset == NULL) throw std::runtime_error(file + " - can't open file asset");

    _descriptor = AAsset_openFileDescriptor(
        asset, &_start, &_length);
    AAsset_close(asset);

    if (_descriptor < 0) throw std::runtime_error("Could not open BGM file");

    SLDataLocator_AndroidFD lDataLocatorIn;
    lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
    lDataLocatorIn.fd          = _descriptor; //lDescriptor.mDescriptor;
    lDataLocatorIn.offset      = _start; // lDescriptor.mStart;
    lDataLocatorIn.length      = _length; // lDescriptor.mLength;

    SLDataFormat_MIME lDataFormat;
    lDataFormat.formatType    = SL_DATAFORMAT_MIME;
    lDataFormat.mimeType      = NULL;
    lDataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

    SLDataSource lDataSource;
    lDataSource.pLocator = &lDataLocatorIn;
    lDataSource.pFormat  = &lDataFormat;

    auto se = soundEngine.lock();
    if (!se) throw std::runtime_error("sound engine not valid");

    SLDataLocator_OutputMix lDataLocatorOut;
    lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    lDataLocatorOut.outputMix   = se->_outMixObj; //mOutputMixObj;

    SLDataSink lDataSink;
    lDataSink.pLocator = &lDataLocatorOut;
    lDataSink.pFormat  = NULL;

    const SLuint32 playerIIDCount = 2;
    const SLInterfaceID playerIIDs[] =
        { SL_IID_PLAY, SL_IID_SEEK };
    const SLboolean playerReqs[] =
        { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

    lRes = (*se->_engine)->CreateAudioPlayer(se->_engine, &_playerObj,
            &lDataSource, &lDataSink, playerIIDCount, playerIIDs,
            playerReqs);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error("can't create player");

    lRes = (*_playerObj)->Realize(_playerObj, SL_BOOLEAN_FALSE);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error("can't realize player");

    lRes = (*_playerObj)->GetInterface(_playerObj, SL_IID_PLAY, &_player);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error("can't get play interface");

    lRes = (*_playerObj)->GetInterface(_playerObj, SL_IID_SEEK, &_playerSeek);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error("can't get seek interface");
}

SLESSound::~SLESSound()
{
}

void SLESSound::play(bool loop) throw (std::runtime_error)
{
    SLresult lRes;

    lRes = (*_playerSeek)->SetLoop(_playerSeek, loop/*SL_BOOLEAN_TRUE*/, 0, SL_TIME_UNKNOWN);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error("can't set loop");

    lRes = (*_player)->SetPlayState(_player, SL_PLAYSTATE_PLAYING);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error("can't play");
}

void SLESSound::stop() throw ()
{
    SLresult lRes;

    lRes = (*_player)->SetPlayState(_player, SL_PLAYSTATE_STOPPED);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error("can't stop");
}

} /* namespace ndk_game */

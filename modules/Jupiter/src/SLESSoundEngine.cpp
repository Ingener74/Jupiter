/*
 * SLESSoundEngine.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#include <Jupiter/SLESSoundEngine.h>
#include <Jupiter/SLESSound.h>

namespace jupiter
{

using namespace std;

SLESSoundEngine::SLESSoundEngine(android_app* app) :
        _app(app)
{
    SLresult lRes;
    const SLuint32 lEngineMixIIDCount = 1;
    const SLInterfaceID lEngineMixIIDs[] =
    { SL_IID_ENGINE };
    const SLboolean lEngineMixReqs[] =
    { SL_BOOLEAN_TRUE };
    const SLuint32 lOutputMixIIDCount = 0;
    const SLInterfaceID lOutputMixIIDs[] =
    { };
    const SLboolean lOutputMixReqs[] =
    { };

    lRes = slCreateEngine(&_engineObj, 0, NULL, lEngineMixIIDCount,
            lEngineMixIIDs, lEngineMixReqs);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error(
            "can't create sound engine");

    lRes = (*_engineObj)->Realize(_engineObj, SL_BOOLEAN_FALSE);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error(
            "can't realize engine");

    lRes = (*_engineObj)->GetInterface(_engineObj, SL_IID_ENGINE, &_engine);
    if (lRes != SL_RESULT_SUCCESS) throw std::runtime_error(
            "can't get engine interface");

    lRes = (*_engine)->CreateOutputMix(_engine, &_outMixObj, lOutputMixIIDCount,
            lOutputMixIIDs, lOutputMixReqs);

    lRes = (*_outMixObj)->Realize(_outMixObj,
    SL_BOOLEAN_FALSE);

    Log() << "OpenSL ES started successfully";
}

SLESSoundEngine::~SLESSoundEngine()
{
    if (_outMixObj != NULL)
    {
        (*_outMixObj)->Destroy(_outMixObj);
        _outMixObj = NULL;
    }
    if (_engineObj != NULL)
    {
        (*_engineObj)->Destroy(_engineObj);
        _engineObj = NULL;
        _engine = NULL;
    }
}

ISound::Ptr SLESSoundEngine::loadSound(const std::string& file)
{
    return make_shared<SLESSound>(_app, file, shared_from_this());
}

} /* namespace ndk_game */

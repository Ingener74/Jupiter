/*
 * DummySoundEngine.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#include <Jupiter/DummySoundEngine.h>
#include <Jupiter/DummySound.h>

namespace ndk_game
{

DummySoundEngine::DummySoundEngine()
{
    // TODO Auto-generated constructor stub

}

DummySoundEngine::~DummySoundEngine()
{
    // TODO Auto-generated destructor stub
}

ISound::Ptr DummySoundEngine::loadSound(const std::string& file)
{
    return std::make_shared<DummySound>();
}

} /* namespace ndk_game */

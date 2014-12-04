/*
 * DummySoundEngine.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#include <Jupiter/DummySoundEngine.h>
#include <Jupiter/DummySound.h>

namespace jupiter
{

using namespace std;

shared_ptr<ISound> DummySoundEngine::loadSound(const string& file)
{
    return make_shared<DummySound>();
}

} /* namespace ndk_game */

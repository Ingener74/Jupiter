/*
 * DummySoundEngine.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef DUMMYSOUNDENGINE_H_
#define DUMMYSOUNDENGINE_H_

#include <memory>
#include <string>
#include <Jupiter/ISoundEngine.h>

namespace jupiter
{

class DummySoundEngine: public ISoundEngine
{
public:
    DummySoundEngine() = default;
    virtual ~DummySoundEngine() = default;

    virtual std::shared_ptr<ISound> loadSound(const std::string& file);
};

} /* namespace ndk_game */

#endif /* DUMMYSOUNDENGINE_H_ */

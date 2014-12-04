/*
 * ISoundEngine.h
 *
 *  Created on: Jun 2, 2014
 *      Author: ingener
 */

#ifndef ISOUNDENGINE_H_
#define ISOUNDENGINE_H_

#include <memory>
#include <string>

namespace jupiter
{

class ISound;

class ISoundEngine
{
public:
    virtual ~ISoundEngine() = default;

    virtual std::shared_ptr<ISound> loadSound(const std::string& file) = 0;

protected:
    ISoundEngine() = default;
};

} /* namespace ndk_game */

#endif /* ISOUNDENGINE_H_ */

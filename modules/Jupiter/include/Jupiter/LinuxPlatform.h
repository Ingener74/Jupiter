/*
 * LinuxPlatform.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_LINUXPLATFORM_H_
#define MODULES_JUPITER_INCLUDE_LINUXPLATFORM_H_

#include <string>

namespace jupiter
{

class LinuxPlatform
{
public:
    LinuxPlatform(const std::string& game);
    virtual ~LinuxPlatform();
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_LINUXPLATFORM_H_ */

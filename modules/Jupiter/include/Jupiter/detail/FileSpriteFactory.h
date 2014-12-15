/*
 * FileSpriteFactory.h
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#ifndef FILESPRITEFACTORY_H_
#define FILESPRITEFACTORY_H_

#include <Jupiter/detail/SpriteBuilder.h>

namespace jupiter
{

class FileSpriteFactory: public SpriteBuilder::Factory
{
public:
    FileSpriteFactory();
    virtual ~FileSpriteFactory();

    virtual std::shared_ptr<SpriteImpl> create(const std::string& spriteId);
};

} /* namespace jupiter */

#endif /* FILESPRITEFACTORY_H_ */

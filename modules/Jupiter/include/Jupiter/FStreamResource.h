/*
 * FStreamResource.h
 *
 *  Created on: Aug 13, 2014
 *      Author: pavel
 */

#ifndef FSTREAMRESOURCE_H_
#define FSTREAMRESOURCE_H_

#include <Jupiter/ResourceManager.h>

namespace jupiter {

class FstreamResource: public ResourceManager::IFactory
{
public:
    FstreamResource() = default;
    virtual ~FstreamResource() = default;

    virtual ResourceManager::Resource createResource( const std::string& fileName );
};

}  // namespace jupiter



#endif /* FSTREAMRESOURCE_H_ */

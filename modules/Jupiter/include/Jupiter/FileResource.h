/*
 * FileResource.h
 *
 *  Created on: Dec 2, 2014
 *      Author: pavel
 */

#ifndef FILERESOURCE_H_
#define FILERESOURCE_H_

#include <string>
#include <Jupiter/ResourceManager.h>

namespace jupiter
{

class FileResource: public ResourceManager::IFactory
{
public:
    FileResource() = default;
    virtual ~FileResource() = default;

    virtual ResourceManager::Resource createResource(const std::string& fileName);
};

} /* namespace jupiter */

#endif /* FILERESOURCE_H_ */

/*
 * ResourceManager.h
 *
 *  Created on: Aug 8, 2014
 *      Author: pavel
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <iostream>
#include <list>
#include <memory>
#include <string>

namespace jupiter
{

class ResourceManager
{
public:
    using Resource = std::shared_ptr<std::istream>;

    class Factory
    {
    public:
        virtual Resource createResource(const std::string& fileName) = 0;
    };

    static void setFactory(std::shared_ptr<Factory> factory);
    static Resource createResource(const std::string& filename);

    static std::string pathPrefix();
    static void setPathPrefix(const std::string& pathPrefix);

private:
    ResourceManager() = default;
    virtual ~ResourceManager() = default;

    static std::list<std::shared_ptr<Factory>>& Register();

    static std::string& PathPrefix();
};

} /* namespace jupiter */

#endif /* RESOURCEMANAGER_H_ */

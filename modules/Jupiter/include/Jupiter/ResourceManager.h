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

    class IFactory
    {
    public:
        IFactory() = default;
        virtual Resource createResource(const std::string& fileName) = 0;

    protected:
        virtual ~IFactory() = default;
    };

    static Resource createResource(const std::string& filename);
    static void pushResourceFactory(std::shared_ptr<IFactory> factory);
    static void popResourceFactory();

private:
    ResourceManager() = default;
    virtual ~ResourceManager() = default;

    static std::list<std::shared_ptr<IFactory>>& Register();
};

} /* namespace jupiter */

#endif /* RESOURCEMANAGER_H_ */

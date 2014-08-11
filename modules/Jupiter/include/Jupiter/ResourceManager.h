/*
 * ResourceManager.h
 *
 *  Created on: Aug 8, 2014
 *      Author: pavel
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <Jupiter/Common.h>

namespace jupiter
{

class ResourceManager
{
public:

	using Resource = std::shared_ptr<std::istream>;
	using Ptr = std::shared_ptr<ResourceManager>;

	class IFactory
	{
	public:
		using Ptr = std::shared_ptr<IFactory>;

		virtual Resource createResource(const std::string& fileName) = 0;
	};

	static Ptr instance();

	virtual ~ResourceManager();

	Resource createResource(const std::string& filename);

	static void pushResourceFactory(IFactory::Ptr factory);
	static void popResourceFactory();

private:
	ResourceManager();

	static std::list<IFactory::Ptr>& Register();
};

} /* namespace jupiter */

#endif /* RESOURCEMANAGER_H_ */

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

	ResourceManager();
	virtual ~ResourceManager();

	static Resource createResource(const std::string& filename);
};

} /* namespace jupiter */

#endif /* RESOURCEMANAGER_H_ */

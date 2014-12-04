/*
 * FStreamResource.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: pavel
 */

#include <memory>
#include <iostream>
#include <fstream>
#include <Jupiter/FStreamResource.h>

namespace jupiter
{

using namespace std;

ResourceManager::Resource FstreamResource::createResource(const std::string& fileName)
{
    return make_shared<ifstream>(fileName);
}

}  // namespace jupiter


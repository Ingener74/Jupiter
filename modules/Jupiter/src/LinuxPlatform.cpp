/*
 * LinuxPlatform.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#include <boost/filesystem.hpp>

#include <Jupiter/LinuxPlatform.h>

//#include <Jupiter/ResourceManager.h>
//#include <Jupiter/FileResource.h>
//
//#include <Jupiter/TextureBuilder.h>
//#include "Factories/ImageTextureFactory.h"
//
//#include <Jupiter/ImageBuilder.h>
//#include <Jupiter/PNGImageFactory.h>
//
//#include <Jupiter/Builder.h>
//#include <Jupiter/FileShaderFactory.h>
//#include <Jupiter/CPPControllerFactory.h>

namespace jupiter
{

using namespace std;

LinuxPlatform::LinuxPlatform(const std::string& gameFileName)
{
    boost::filesystem::path game{gameFileName};

//    ResourceManager::setPathPrefix(game.parent_path().c_str());
//    ResourceManager::setFactory(make_shared<FileResource>());
//
//    TextureBuilder::addFactory("file", make_shared<ImageTextureFactory>());
//    ImageBuilder::addFactory("png", make_shared<PNGImageFactory>());
//    ImageBuilder::addFactory("PNG", make_shared<PNGImageFactory>());

//    Builder<Shader, ShaderImpl>::addFactory("file", make_shared<FileShaderFactory>());
//
//    Builder<Controller, ControllerImpl>::addFactory("c++", make_shared<CPPControllerFactory>());
//
//    Builder<Game, GameImpl>::addFactory("file", make_shared<JSONGameFactory>());
//
//    Builder<Node, NodeImpl>::addFactory("json", make_shared<JSONNodeFactory>());
}

LinuxPlatform::~LinuxPlatform()
{
}

} /* namespace jupiter */

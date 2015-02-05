/*
 * Game.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: ingener
 */

#include <boost/filesystem.hpp>

#include <Jupiter/Game.h>
#include <Jupiter/TextureBuilder.h>
#include <Jupiter/ResourceManager.h>
#include <Jupiter/FileResource.h>
#include <Jupiter/PNGImageFactory.h>
#include <Jupiter/JupiterError.h>

#include <Jupiter/FileShaderFactory.h>
#include <Jupiter/CPPControllerFactory.h>

#include "Factories/ImageTextureFactory.h"

#include <Jupiter/Node.h>

namespace jupiter
{

using namespace std;
using namespace glm;

Game::Game()
{
//    int width = 100, height = 100;
//    render = {ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100)};
}

template<typename T>
class Store
{
public:
    Store() = delete;
    virtual ~Store() = delete;

    static void put(const string& name, shared_ptr<T> impl)
    {
        Register()[name] = impl;
    }
    static shared_ptr<T> get(const string& name)
    {
        return Register()[name];
    }
private:
    using Reg = map<string, shared_ptr<T>>;
    static Reg& Register()
    {
        static Reg reg;
        return reg;
    }
};

Game::~Game()
{
}

void Game::draw()
{
    render.visit(*node);
}

void Game::input()
{
}

int32_t Game::getWidth() const
{
    return width;
}

int32_t Game::getHeight() const
{
    return height;
}

} /* namespace jupiter */

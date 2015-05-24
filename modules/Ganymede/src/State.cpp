/*
 * State.cpp
 *
 *  Created on: Aug 15, 2014
 *      Author: pavel
 */

#include <iostream>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "Ganymede/State.h"

namespace ganymede
{

using namespace std;

State::State()
{
	_L = luaL_newstate();
	luaL_openlibs(_L);
}

State& State::load(std::istream& in)
{
	load(string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()));

	return *this;
}

State& State::load(const std::string& program)
{
	luaL_loadstring(_L, program.c_str());

	lua_pcall(_L, 0, 0, 0);

	return *this;
}

State::~State()
{
	lua_close(_L);
}

} /* namespace ganymede */

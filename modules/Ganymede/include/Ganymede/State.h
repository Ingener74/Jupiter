/*
 * State.h
 *
 *  Created on: Aug 15, 2014
 *      Author: pavel
 */

#ifndef STATE_H_
#define STATE_H_

#include <string>

struct lua_State;

namespace ganymede
{

class State
{
public:
	State();

	template<typename T>
	T& get();

	State& load(std::istream& in);
	State& load(const std::string& program);

	virtual ~State();

private:
	lua_State* _L = nullptr;
};

template<typename T>
inline T& State::get()
{
}

} /* namespace ganymede */


#endif /* STATE_H_ */

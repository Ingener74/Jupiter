/*
 * main.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

#include <lua.hpp>
#include <lparser.h>

using namespace std;

int main( int argc, char **argv )
{
    try
    {
        cout << "Parse lua test" << endl;

        if ( argc < 2 ) throw runtime_error(""
                "Usage: ./lua_parse_test <path-to-lua-file>");

        lua_State* L = luaL_newstate();

//		luaY_parser(L, )

        lua_close(L);

        return 0;
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}


/*
 * main.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: pavel
 */

#include <fstream>
#include <iterator>
#include <iostream>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include <GL/glew.h>
#include <GL/glut.h>

#include <lua.hpp>

using namespace std;
using namespace boost;

filesystem::path gameFileLocation;

int x = 0;
int y = 0;
int width = 0;
int height = 0;

/*
 * Lua functions
 */
extern "C" {

static int lua_getGameLocation( lua_State* L )
{
    lua_pushstring(L, gameFileLocation.parent_path().c_str());
    return 1;
}

}

/*
 * Other functions
 */
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.4f, 0.2f, 1.f);

    glutSwapBuffers();
}

void reshape( int w, int h )
{
    glViewport(0, 0, w, h);
}

int main( int argc, char **argv )
{
    try
    {
        cout << "Jupiter game player" << endl;

        if ( argc < 2 ) throw runtime_error(""
                "Usage  : ./GamePlayer <path-to-game>\n"
                "Example: ./GamePlayer ~/games/Asteroids/Asteroids.lua");

        /*
         * read program from lua file
         *
         *  -- set ortho projection
         *  -- create engine
         */

        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        lua_register(L, "getGameLocation", lua_getGameLocation);

        gameFileLocation = filesystem::path(argv[ 1 ]);

        luaL_loadfile(L, argv[1]);
        lua_pcall(L, 0, 0, 0);

        {
            lua_getglobal(L, "viewport");
            if ( !lua_istable(L, -1) ) throw runtime_error("can't find viewport table");
            {
                lua_getfield(L, -1, "x");
                if ( !lua_isnumber(L, -1) ) throw runtime_error("can't find x in viewport table");
                x = (int) lua_tonumber(L, -1);
                lua_pop(L, 1);
            }
            {
                lua_getfield(L, -1, "y");
                if ( !lua_isnumber(L, -1) ) throw runtime_error("can't find y in viewport table");
                y = (int) lua_tonumber(L, -1);
                lua_pop(L, 1);
            }
            {
                lua_getfield(L, -1, "width");
                if ( !lua_isnumber(L, -1) ) throw runtime_error("can't find width in viewport table");
                width = (int) lua_tonumber(L, -1);
                lua_pop(L, 1);
            }
            {
                lua_getfield(L, -1, "height");
                if ( !lua_isnumber(L, -1) ) throw runtime_error("can't find height in viewport table");
                height = (int) lua_tonumber(L, -1);
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }

//        glutInit(&argc, argv);
//        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//        glutInitWindowSize(width, height);
//        glutCreateWindow("Jupiter game player");
//
//        glutReshapeFunc(reshape);
//        glutDisplayFunc(display);
//        glutIdleFunc(display);
//
//        if ( glewInit() != GLEW_OK ) throw runtime_error("glew init error");
//
//        glViewport(x, y, width, height);
//
//        glutMainLoop();

        lua_close(L);

        return EXIT_SUCCESS;
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


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

#include <selene.h>

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
 * Code
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
        gameFileLocation = filesystem::path(argv[ 1 ]);

        sel::State state{true};
        state.Load(argv[1]);

        x = state["viewport"]["x"];
        y = state["viewport"]["y"];
        width = state["viewport"]["width"];
        height = state["viewport"]["height"];

        cout << x << " " << y << " " << width << " " << height << endl;



//        state["getGameLocation"] = &lua_getGameLocation;

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

        return EXIT_SUCCESS;
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


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

#include <selene.h>

#include <Jupiter/Jupiter.h>

using namespace std;
using namespace boost;
using namespace jupiter;

filesystem::path gameFileLocation;

int x = 0;
int y = 0;
int width = 0;
int height = 0;

DrawEngine::Ptr engine;

/*
 * Code
 */
string getGameLocation()
{
	return string(gameFileLocation.parent_path().c_str());
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

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

        gameFileLocation = filesystem::path(argv[ 1 ]);

        sel::State L{true};

        L["getGameLocation"] = &getGameLocation;

        L.Load(argv[1]);

        x = L["viewport"]["x"];
        y = L["viewport"]["y"];
        width = L["viewport"]["width"];
        height = L["viewport"]["height"];

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow("Jupiter game player");

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);

        if ( glewInit() != GLEW_OK ) throw runtime_error("glew init error");

        glViewport(x, y, width, height);

//        engine = make_shared<DrawEngine>(make_shared<SimpleShaderLoader>(),);

        glutMainLoop();

        return EXIT_SUCCESS;
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


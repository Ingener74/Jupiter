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
#include <boost/program_options.hpp>

#include <GL/glew.h>
#include <GL/glut.h>

#include <selene.h>

#include <Jupiter/Jupiter.h>

using namespace std;
using namespace glm;
using namespace sel;
using namespace jupiter;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::program_options;

path gameFileLocation;

int x = 0;
int y = 0;
int width = 0;
int height = 0;

std::shared_ptr<State> luaState;
DrawEngine::Ptr engine;

string usage = ""
        "Usage  : ./GamePlayer -g <path-to-game>\n"
        "Example: ./GamePlayer -g ~/games/Asteroids/Asteroids.lua";

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

    engine->draw();

    glutSwapBuffers();
}

void reshape( int w, int h )
{
    glViewport(0, 0, w, h);
}

int main( int argc, char **argv )
{
    options_description desc("General description");
    try
    {
        cout << "Jupiter game player" << endl;

        desc.add_options()("help,h", "Show help")("game,g", value<std::string>(), "Path to game file");
        variables_map vm;

        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if ( vm.count("help") )
        {
            desc.print(std::cout);
            std::cout << usage << endl;
            return 0;
        }

        if ( !vm.count("game") ) throw JupiterError("have no game file");

        gameFileLocation = path(vm[ "game" ].as<string>());

        luaState = make_shared<State>(true);

        (*luaState)[ "getGameLocation" ] = &getGameLocation;

        luaState->Load(vm[ "game" ].as<string>());

        x = (*luaState)[ "viewport" ][ "x" ];
        y = (*luaState)[ "viewport" ][ "y" ];
        width = (*luaState)[ "viewport" ][ "width" ];
        height = (*luaState)[ "viewport" ][ "height" ];

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow("Jupiter game player");

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);

        if ( glewInit() != GLEW_OK ) throw runtime_error("glew init error");

        glViewport(x, y, width, height);

        auto o = ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100);

        ResourceManager::pushResourceFactory(make_shared<FstreamResource>());

        string vs = (*luaState)[ "program" ][ "vertex" ], fs = (*luaState)[ "program" ][ "fragment" ];

        engine = make_shared<DrawEngine>(
                make_shared<ResourceShaderLoader>(getGameLocation() + "/" + vs, getGameLocation() + "/" + fs), o, width,
                height);

        auto mainScene = make_shared<Scene>();
        engine->setCurrentScene(mainScene);

        glutMainLoop();

        return EXIT_SUCCESS;
    }
    catch ( std::exception const & e )
    {
        desc.print(std::cerr);
        cerr << usage << endl << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


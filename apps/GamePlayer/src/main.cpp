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
using namespace glm;
using namespace jupiter;
using namespace sel;

filesystem::path gameFileLocation;

int x = 0;
int y = 0;
int width = 0;
int height = 0;

std::shared_ptr<State> luaState;
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

        /*
         * boost program options
         */

        if ( argc < 2 ) throw runtime_error(""
                "Usage  : ./GamePlayer <path-to-game>\n"
                "Example: ./GamePlayer ~/games/Asteroids/Asteroids.lua");

        gameFileLocation = filesystem::path(argv[ 1 ]);

        luaState = make_shared<State>(true);
//        sel::State L{true};

        (*luaState)["getGameLocation"] = &getGameLocation;

        luaState->Load(argv[1]);

        x = (*luaState)["viewport"]["x"];
        y = (*luaState)["viewport"]["y"];
        width = (*luaState)["viewport"]["width"];
        height = (*luaState)["viewport"]["height"];

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

        class DummyShaderLoader: public IShaderLoader
        {
        public:
            DummyShaderLoader(std::shared_ptr<State> L): _L(L)
            {
            }
            virtual ~DummyShaderLoader()
            {
            }

            virtual string getVertexShader() const
            {
                string fn = (*_L)[ "program" ][ "vertex" ];
                cout << fn << endl;
                fstream file(fn);
                return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            }
            virtual string getFragmentShader() const
            {
                string fn = (*_L)[ "program" ][ "fragment" ];
                fstream file(fn);
                return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            }

        private:
            std::shared_ptr<State> _L;
        };

        /*a->activity->assetManager, "shader/vertex.shader", "shader/fragment.shader"*/
        engine = make_shared<DrawEngine>(make_shared<DummyShaderLoader>(luaState), o, width, height);

        glutMainLoop();

        return EXIT_SUCCESS;
    }
    catch ( std::exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


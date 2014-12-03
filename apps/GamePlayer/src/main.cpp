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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <GL/glew.h>
#include <GL/glut.h>

//#include <selene.h>

#include <Ganymede/Ganimede.h>
#include <Jupiter/Jupiter.h>

using namespace std;
using namespace glm;
//using namespace sel;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::program_options;

using namespace ganymede;
using namespace jupiter;

path gameFileLocation;

int x = 0;
int y = 0;
int width = 0;
int height = 0;

//std::shared_ptr<State> luaState;
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

void createScene(const string& sceneName)
{
    cout << "create scene " << sceneName << endl;
}

void createSceneNumber(int i)
{
    cout << "create scene number " << i << endl;
}

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    engine->draw();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{
    options_description desc("General description");
    try
    {
        cout << "Jupiter game player" << endl;

        desc.add_options()("help,h", "Show help")("game,g", value<std::string>(), "Path to game file");
        variables_map vm;

        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help"))
        {
            cout << desc << endl << usage << endl;
            return 0;
        }

        if (!vm.count("game")) throw runtime_error("have no game file");

        ResourceManager::pushResourceFactory(make_shared<FileResource>());

        gameFileLocation = path(vm["game"].as<string>());

        ganymede::State L;

        property_tree::ptree pt;

        auto file = ResourceManager::instance()->createResource(vm["game"].as<string>());
        property_tree::json_parser::read_json(*file, pt);

        cout << "name = " << pt.get<string>("name") << endl;

        cout << "w = " << pt.get<int>("resolution.width") << endl;
        cout << "h = " << pt.get<int>("resolution.height") << endl;

        cout << "texture_dir = " << pt.get<string>("texture_dir") << endl;

//        L.load(*file);

//        luaState = make_shared<State>(true);
//
//		(*luaState)["getGameLocation"] = &getGameLocation;
//		(*luaState)["createScene"] = &createScene;
//		(*luaState)["createSceneNumber"] = &createSceneNumber;
//
//        luaState->Load(vm[ "game" ].as<string>());
//
//        x = (*luaState)[ "viewport" ][ "x" ];
//        y = (*luaState)[ "viewport" ][ "y" ];
//        width = (*luaState)[ "viewport" ][ "width" ];
//        height = (*luaState)[ "viewport" ][ "height" ];

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow("Jupiter game player");

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);

        if (glewInit() != GLEW_OK) throw runtime_error("glew init error");

        glViewport(x, y, width, height);

        auto o = ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100);

        string vs = /*(*luaState)[ "program" ][ "vertex" ]*/"resources/shaders/vertex.shader",
                fs = /*(*luaState)[ "program" ][ "fragment" ]*/"resources/shaders/fragment.shader";

        engine = make_shared<DrawEngine>(
                make_shared<ResourceShaderLoader>(getGameLocation() + "/" + vs, getGameLocation() + "/" + fs), o, width,
                height);

        auto mainScene = make_shared<Scene>();
        engine->setCurrentScene(mainScene);

        glutMainLoop();

        return EXIT_SUCCESS;
    }
    catch (std::exception const & e)
    {
        cerr << desc << endl << usage << endl << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


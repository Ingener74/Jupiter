/*
 * main.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: pavel
 */

#include <map>
#include <memory>
#include <fstream>
#include <iterator>
#include <iostream>
#include <stdexcept>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GL/glut.h>

//#include <selene.h>

#include <Jupiter/Jupiter.h>
#include <Ganymede/Ganimede.h>

/*
 * Old game controller
 */
#include <Tools.h>
#include <BackGround.h>
#include <BattleShip.h>
#include <Life.h>
#include <StartButton.h>

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
std::shared_ptr<DrawEngine> engine;

string usage = ""
        "Usage  : ./GamePlayer -g <path-to-game>\n"
        "Example: ./GamePlayer -g ~/games/Asteroids/Asteroids.lua";

/*
 * Code
 */
void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    engine->animateAll(1000.0 / 60.0);

    engine->draw();

    /*
     * game->getEngine()->draw();
     */

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

        ganymede::State L;

        gameFileLocation = path(vm["game"].as<string>());

        {
            /*
             * Jupiter internal settings
             */
            ResourceManager::setPathPrefix(gameFileLocation.parent_path().c_str());
            ResourceManager::pushResourceFactory(make_shared<FileResource>());

            ImageBuilder::addFactory("png", make_shared<PNGImageFactory>());
            ImageBuilder::addFactory("PNG", make_shared<PNGImageFactory>());
        }

        auto file = ResourceManager::createResource(gameFileLocation.filename().c_str());

        property_tree::ptree pt;
        property_tree::json_parser::read_json(*file, pt);

        width  = pt.get<int>("resolution.width");
        height = pt.get<int>("resolution.height");

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow("Jupiter game player");

//        glEnable(GL_CULL_FACE);
//        glEnable(GL_DEPTH_TEST);
//
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);

        if (glewInit() != GLEW_OK) throw runtime_error("glew init error");

        glViewport(x, y, width, height);

        auto o = ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100);

        string vs = "resources/shaders/vertex.shader", fs = "resources/shaders/fragment.shader";

        engine = make_shared<DrawEngine>(make_shared<ResourceShaderLoader>(vs, fs), o, width, height);

//        Image im(getGameLocation() + "/resources/images/bg.png");
//        cout << "image " << im << endl;

        auto startScene = make_shared<Scene>();
        auto mainScene = make_shared<Scene>();
        auto winScene = make_shared<Scene>();
        auto failScene = make_shared<Scene>();

        map<string, std::shared_ptr<Scene>> gameScenes;
        gameScenes["Start"] = startScene;
        gameScenes["Main"] = mainScene;
        gameScenes["Win"] = winScene;
        gameScenes["Fail"] = failScene;

        auto tools = GameTools{
            [&](const string& sceneName){ return gameScenes[sceneName]; },
            [=](std::shared_ptr<Scene> scene){ engine->setCurrentScene(scene); }
        };

        auto dummySE = make_shared<DummySoundEngine>();

        auto background = make_shared<BackGround>();

        {
            /*
             * Start scene
             */
            startScene->gameObject = {
                    background,
                    make_shared<StartButton>(width, height, tools)
            };
        }

        {
            /*
             * Main scene
             */
            auto life = make_shared<Life>(width, height, tools);
            auto battleShip = make_shared<BattleShip>(width, height, life, dummySE, tools);

            mainScene->gameObject = {background, battleShip, life};
        }

        engine->setCurrentScene(startScene);

//        map<string, std::shared_ptr<IGameObject>> gameObjects;
//        gameObjects[background->getName()] = background;
//        cout << "game objects" << endl;
//        for(auto i: gameObjects)
//            cout << "game object " << i.first << endl;

        /*
         * auto gameBuilder = make_shader<LinuxGameBuilder>( vm["game"].as<string>() );
         *
         * auto game = gameBuilder->createGame();
         */


        glutMainLoop();

        return EXIT_SUCCESS;
    }
    catch (std::exception const & e)
    {
        cerr << desc << endl;
        cerr << usage << endl;
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


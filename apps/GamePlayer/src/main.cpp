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

#include "TempAsteroidsControllers/BackGround.h"

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

        ResourceManager::pushResourceFactory(make_shared<FileResource>());

        gameFileLocation = path(vm["game"].as<string>());

        ganymede::State L;

        property_tree::ptree pt;

        auto file = ResourceManager::createResource(vm["game"].as<string>());
        property_tree::json_parser::read_json(*file, pt);

        width  = pt.get<int>("resolution.width");
        height = pt.get<int>("resolution.height");

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

        string vs = "resources/shaders/vertex.shader" /*(*luaState)[ "program" ][ "vertex" ]*/,
                fs = "resources/shaders/fragment.shader" /*(*luaState)[ "program" ][ "fragment" ]*/;

        engine = make_shared<DrawEngine>(
                make_shared<ResourceShaderLoader>(getGameLocation() + "/" + vs, getGameLocation() + "/" + fs),
                o, width, height);

        auto mainScene = make_shared<Scene>();

//        class BackGround: public IGameObject
//        {
//        public:
//            BackGround()
//            {
//                auto textureLoader = std::make_shared<FileTextureLoader>(getGameLocation() + "/resources/images/rocks1.png");
//
//                auto texture = Texture::create(textureLoader);
//
//                auto rect = std::make_shared<RectSpriteLoader>(100, 100, 0, 0, 1, 0, 1);
//
//                background = std::make_shared<Sprite>(texture, rect);
//            }
//            virtual ~BackGround()
//            {
//            }
//
//            virtual void update(double elapsed) throw (JupiterError)
//            {
//                throw JupiterError("test");
//            }
//            virtual list<std::shared_ptr<Sprite>> getSprites() const throw ()
//            {
//                return {background};
//            }
//            virtual string getName() const throw ()
//            {
//                return "Test Background";
//            }
//
//        private:
//            std::shared_ptr<Sprite> background;
//        };

        auto background = make_shared<BackGround>([](){ return getGameLocation(); });

        mainScene->gameObject.push_back(background);

        engine->setCurrentScene(mainScene);

        map<string, std::shared_ptr<IGameObject>> gameObjects;

        gameObjects[background->getName()] = background;

        cout << "game objects" << endl;
        for(auto i: gameObjects)
            cout << "game object " << i.first << endl;

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
        cerr << desc << endl << usage << endl << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}


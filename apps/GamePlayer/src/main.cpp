/*
 * main.1   cpp
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

#include <Jupiter.h>
#include <Ganymede/Ganimede.h>

/*
 * Old game controller
 */
//#include <Tools.h>
//#include <BackGround.h>
//#include <BattleShip.h>
//#include <Life.h>
//#include <StartButton.h>
//#include <Rock.h>
//#include <GameAgain.h>
//#include <FireButton.h>
//#include <GasButton.h>
//#include <LeftButton.h>
//#include <RightButton.h>
//#include <WinAgain.h>

/*
 * New game controllers
 */

using namespace std;
using namespace glm;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::program_options;

using namespace ganymede;
using namespace jupiter;

/*
 * -- preload/caching images in before node in tree
 *
 * -- sound
 *
 * -- animation node
 *
 * -- text node
 */

Game game;

string usage = R"(
Usage  : ./GamePlayer -g <path-to-game>
Example: ./GamePlayer -g ~/games/Asteroids/Asteroids.lua
)";

/*
 * Code
 */
void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    game.draw();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void mouse(int button, int action, int x, int y)
{
    static map<int, string> buttons{
        {GLUT_LEFT_BUTTON,   "GLUT_LEFT_BUTTON"},
        {GLUT_MIDDLE_BUTTON, "GLUT_MIDDLE_BUTTON"},
        {GLUT_RIGHT_BUTTON,  "GLUT_RIGHT_BUTTON"},
    };
    static map<int, string> actions{
        {GLUT_DOWN, "GLUT_DOWN"},
        {GLUT_UP,   "GLUT_UP"}
    };
//    cout << buttons[button] << " " << actions[action] << " " << x << " x " << y << endl;

    game.input();
}

void mouseMove( int x, int y )
{
    game.input();
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

//        gameFileLocation = path(vm["game"].as<string>());
//        auto file = ResourceManager::createResource(gameFileLocation.filename().c_str());
//        property_tree::ptree pt;
//        property_tree::json_parser::read_json(*file, pt);
//        width  = pt.get<int>("resolution.width");
//        height = pt.get<int>("resolution.height");

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(800, 480);
        glutCreateWindow("Jupiter game player");

        glEnable(GL_DEPTH_TEST);
//
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);

        if (glewInit() != GLEW_OK) throw runtime_error("glew init error");

        game = Game(vm["game"].as<string>());

//        auto script = ResourceManager::createResource("Asteroids.lua");
//        ganymede::State L;
//        L.load(*script);

        glViewport(0, 0, game.width(), game.height());

//        auto o = ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100);

//        string vs = "resources/shaders/vertex.shader", fs = "resources/shaders/fragment.shader";
//        engine = make_shared<DrawEngine>(make_shared<ResourceShaderLoader>(vs, fs), o, width, height);

//        map<string, std::shared_ptr<Scene>> gameScenes;
//        gameScenes["Start"] = make_shared<Scene>();
//        gameScenes["Main"]  = make_shared<Scene>();
//        gameScenes["Win"]   = make_shared<Scene>();
//        gameScenes["Fail"]  = make_shared<Scene>();
//
//        auto tools = GameTools{
//            [&](const string& sceneName){ return gameScenes[sceneName]; },
//            [=](std::shared_ptr<Scene> scene){ engine->setCurrentScene(scene); }
//        };
//
//        auto dummySE = make_shared<DummySoundEngine>();
//        auto background = make_shared<BackGround>();

        /*
         * Start scene
         */
//        gameScenes["Start"]->gameObject = {
//                background,
//                make_shared<StartButton>(width, height, tools)
//        };

        /*
         * Main scene
         */

//        auto newGame = [&]()
//        {
//            auto life = make_shared<Life>(width, height, tools);
//            auto battleShip = make_shared<BattleShip>(width, height, life, dummySE, tools);
//
//            Rock::reset();
//            auto rock1 = Rock::createRock(width, height, dummySE, vec3{}, tools);
//            auto rock2 = Rock::createRock(width, height, dummySE, vec3{}, tools);
//            auto rock3 = Rock::createRock(width, height, dummySE, vec3{}, tools);
//
//            auto fireButton = make_shared<FireButton>(width, height, battleShip);
//            auto gasButton = make_shared<GasButton>(width, height, battleShip);
//            auto rightButton = make_shared<RightButton>(width, height, battleShip);
//            auto leftButton = make_shared<LeftButton>(width, height, battleShip);
//
//            gameScenes["Main"]->gameObject = {
//                    background,
//                    battleShip,
//                    fireButton,
//                    gasButton,
//                    rightButton,
//                    leftButton,
//                    rock1.front(),
//                    rock2.front(),
//                    rock3.front(),
//                    life,
//            };
//        };
//        newGame();

        /*
         * Win scene
         */
//        auto winButton = make_shared<WinAgain>(width, tools, newGame);
//        gameScenes["Win"]->gameObject = {
//                background,
//                winButton
//        };

        /*
         * Lose scene
         */
//        auto failButton = make_shared<GameAgain>(width, tools, newGame);
//        gameScenes["Fail"]->gameObject = {
//                background,
//                failButton
//        };

//        engine->setCurrentScene(gameScenes["Start"]);

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


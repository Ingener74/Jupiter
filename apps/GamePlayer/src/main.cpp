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

unique_ptr<Game> game;

string usage = R"(
Usage  : ./GamePlayer -g <path-to-game>
Example: ./GamePlayer -g ~/games/Asteroids/Asteroids.lua
)";

/*
 * Code
 */
void display(void) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    game->draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void mouse(int button, int action, int x, int y) {
    static map<int, string> buttons{
        { GLUT_LEFT_BUTTON, "GLUT_LEFT_BUTTON" },
        { GLUT_MIDDLE_BUTTON, "GLUT_MIDDLE_BUTTON" },
        { GLUT_RIGHT_BUTTON, "GLUT_RIGHT_BUTTON" },
    };
    static map<int, string> actions{
        { GLUT_DOWN, "GLUT_DOWN" },
        { GLUT_UP, "GLUT_UP" }
    };

    game->input();
}

void mouseMove(int x, int y) {
    game->input();
}

unique_ptr<BufferFactory> bufferFactory;
unique_ptr<RenderVisitor> render;
unique_ptr<Shader> spriteShader;
unique_ptr<Node> rootNode;
unique_ptr<Sprite> bg, flour, box;
unique_ptr<Shape> bgShape, flourShape, boxShape;
unique_ptr<Controller> boxController;
unique_ptr<Texture> bgTexture, flourTexture, boxTexture;

void create_game(){

    bufferFactory = make_unique_<LinuxFileFactory>();
    File::setBufferFactory(bufferFactory.get());
    File::setBase("samples/Box");

//    spriteShader = make_unique_<>();

//    PngImage backGroundImage{"Resources/bg.png"};
//    backGroundTexture = make_unique_<ImageTexture>(&backGroundImage);

    bg = make_unique_<Sprite>();

    flour = make_unique_<Sprite>();
    flour->
        setProgram(spriteShader.get())->
        setTexture(bgTexture.get())->
        setShape(bgShape.get());

    box = make_unique_<Sprite>();
    box->
        setProgram(spriteShader.get())->
        setTexture(boxTexture.get())->
        setShape(boxShape.get())->
        setController(boxController.get())->
        setPositionY(100.f);

    rootNode = make_unique_<Node>();
    rootNode->
        addNode(bg.get())->
        addNode(flour.get())->
        addNode(box.get());

    game = make_unique_<Game>();
    game->
        setRootNode(rootNode.get())->
        setRender(render.get());
}

void create_game_from_json(const std::string& fileName){
    path gameFile = fileName;

    bufferFactory = make_unique_<LinuxFileFactory>();
    File::setBufferFactory(bufferFactory.get());
    File::setBase(gameFile.parent_path().native());

    game = make_unique_<JsonGame>(gameFile.filename().native());
}

int main(int argc, char **argv) {
    options_description desc("General description");
    try {
        cout << "Jupiter game player" << endl;

        desc.add_options()
            ("help,h", "Show help")
            ("game,g", value<std::string>(), "Path to game file");
        variables_map vm;

        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            cout << desc << endl;
            cout << usage << endl;
            return EXIT_SUCCESS;
        }

        if (!vm.count("game"))
            throw runtime_error("have no game file");

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(800, 480);
        glutCreateWindow("Jupiter game player");

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutIdleFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(mouseMove);

        if (glewInit() != GLEW_OK)
            throw runtime_error("glew init error");

        create_game();
//        create_game_from_json(vm["game"].as<string>());

        glutReshapeWindow(game->getWidth(), game->getHeight());
        glViewport(0, 0, game->getWidth(), game->getHeight());

        glutMainLoop();

        return EXIT_SUCCESS;
    } catch (std::exception const & e) {
        cerr << desc << endl;
        cerr << usage << endl;
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}


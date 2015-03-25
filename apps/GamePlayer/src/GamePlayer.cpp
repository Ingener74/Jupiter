/*
 * GamePlayer.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: pavel
 */

#include "GamePlayer.h"

#include <Jupiter.h>
#include <Ganymede/Ganimede.h>

using namespace std;
using namespace glm;
using namespace boost::filesystem;
using namespace boost::program_options;

using namespace ganymede;
using namespace jupiter;

string usage = R"(
Usage  : ./GamePlayer -g <path-to-game>
Example: ./GamePlayer -g ~/games/Asteroids/Asteroids.lua
)";

string title =R"(Jupiter Game Player)";

/*
 * Code
 */

unique_ptr<Game> game;

unique_ptr<BufferFactory>   bufferFactory;

unique_ptr<RenderVisitor>   render;
unique_ptr<NodeVisitor>     physics;

unique_ptr<Shader>          spriteShader;

unique_ptr<Node>            rootNode;

unique_ptr<Sprite>          bg,
                            flour,
                            box;

unique_ptr<Shape>           bgShape,
                            flourShape,
                            boxShape;

unique_ptr<Texture>         bgTexture,
                            flourTexture,
                            boxTexture;

unique_ptr<Controller>      boxController;

bool createGame(int argc, char* argv[]) {
    options_description desc("General description");

    desc.add_options()
        ("help,h"   ,                  "Show help")
        ("sample,s" , value<string>(), "Select sample: box or json")
        ("game,g"   , value<string>(), "Path to game file")
        ("base,b"   , value<string>(), "Base directory");
    variables_map vm;

    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        cout << usage << endl;
        return false;
    }

    if (!vm.count("sample"))
        throw runtime_error("select sample");

    if (vm["sample"].as<string>() == "box") {
        MyCreateGameDirect(vm);
        return true;
    } else if (vm["sample"].as<string>() == "json") {
        MyCreateGameJsonFile(vm);
        return true;
    } else {
        throw runtime_error("select sample");
    }
    return false;
}

bool MyCreateGameDirect(const variables_map& vm) {

    if (!vm.count("base"))
        throw runtime_error("base directory is invalid");

    bufferFactory = make_unique_<LinuxFileFactory>();
    File::setBufferFactory(bufferFactory.get());
    File::setBase(vm["base"].as<string>());

    int width = 800, height = 480;
    render = make_unique_<RenderVisitor>(ortho<float>(-width / 2, width / 2, -height / 2, height / 2, -100, 100));

//    physics = make_unique_<PrintVisitor>();
    physics = make_unique_<NodeVisitor>();

    File vs { "Resources/sprite.vs" }, fs { "Resources/sprite.fs" };
    spriteShader = make_unique_<FileShader>(&vs, &fs);

    rootNode = make_unique_<Node>();

    PngImage bgImage { "Resources/bg.png" };
    bgTexture = make_unique_<ImageTexture>(&bgImage);
    bgShape = make_unique_<ImageShape>(&bgImage);

    bg = make_unique_<Sprite>();
    bg
        ->setProgram(spriteShader.get())
        ->setTexture(bgTexture.get())
        ->setShape(bgShape.get())
        ->setVisible(true)
        ->scale(.5f, .5f)
//        ->translateZ(10.f)
        ->rotateZ(M_PI)
        ->setParent(rootNode.get())
    ;

    PngImage flourImage { "Resources/ground.png" };
    flourTexture = make_unique_<ImageTexture>(&flourImage);
    flourShape = make_unique_<ImageShape>(&flourImage);

    flour = make_unique_<Sprite>();
    flour
        ->setProgram(spriteShader.get())
        ->setTexture(flourTexture.get())
        ->setShape(flourShape.get())
        ->setVisible(true)
        ->scale(.8f, .8f)
//        ->translate(0.f, -180.f, -20.f)
        ->translateY(-180.f)
        ->rotateZ(M_PI)
        ->setParent(rootNode.get())
    ;

    PngImage boxImage { "Resources/box.png" };
    boxTexture = make_unique_<ImageTexture>(&boxImage);
    boxShape = make_unique_<ImageShape>(&boxImage);

    box = make_unique_<Sprite>();
    box
        ->setProgram(spriteShader.get())
        ->setTexture(boxTexture.get())
        ->setShape(boxShape.get())
        ->setController(boxController.get())
        ->setVisible(true)
//        ->translate(0.f, 150.f, -10.f)
        ->translateY(150.f)
        ->scale(.1f, .1f)
        ->setParent(rootNode.get())
    ;

    rootNode
        ->addNode(bg.get())
        ->addNode(flour.get())
        ->addNode(box.get())
        ->setVisible(true)
    ;

    game = make_unique_<Game>();
    game

        ->setRootNode(rootNode.get())
        ->setRender(render.get())
        ->setPhysicsEngine(physics.get())
        ->setWidth(width)
        ->setHeight(height)
    ;

    return true;
}

bool MyCreateGameJsonFile(const variables_map& vm) {

    if (!vm.count("game"))
        throw runtime_error("have no game file");

    path gameFile = vm["game"].as<string>();

    bufferFactory = make_unique_<LinuxFileFactory>();
    File::setBufferFactory(bufferFactory.get());
    File::setBase(gameFile.parent_path().native());

    game = make_unique_<JsonGame>(gameFile.filename().native());

    return true;
}

void MyDraw() {

    box->translateZ(.1f);
    flour->translateZ(-.1f);

    game->draw();
}

void MyInput() {
    game->input();
}

std::string getTitle() {
    return "Jupiter Game Player";
}

int getWidth() {
    if (!game)
        throw runtime_error("game is invalid");
    return game->getWidth();
}

int getHeight() {
    if (!game)
        throw runtime_error("game is invalid");
    return game->getHeight();
}


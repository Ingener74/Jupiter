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

using namespace std;
using namespace boost;

filesystem::path gameFileLocation;

void display(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.4f, 0.2f, 1.f);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

extern "C"
{

static int l_new_print(lua_State* L)
{
	for (int i = 1; i < lua_gettop(L) + 1; ++i)
	{
		cout << lua_tostring(L, i);
	}
	cout << endl;
	return 0;
}

static int lua_getGameLocation(lua_State* L)
{
	lua_pushstring(L, gameFileLocation.parent_path().c_str());
	return 1;
}

}

int main(int argc, char **argv)
{
	try
	{
		cout << "Jupiter game player" << endl;

		if (argc < 2) throw runtime_error(""
				"Usage  : ./GamePlayer <path-to-game>\n"
				"Example: ./GamePlayer ~/games/Asteroids/Asteroids.lua");

		/*
		 * read program from lua file
		 *
		 *  -- set viewport
		 *  -- set ortho projection
		 *  -- create engine
		 */

		lua_State* L = luaL_newstate();
		luaL_openlibs(L);

		lua_register(L, "new_print", l_new_print);

		gameFileLocation = filesystem::path(argv[1]);

		fstream file(argv[1]);

		lua_register(L, "getGameLocation", lua_getGameLocation);

		luaL_loadstring(L, string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>()).c_str());

		lua_pcall(L, 0, 0, 0);

		lua_getglobal(L, "viewport");

		if (!lua_istable(L, -1)) throw runtime_error("can't find viewport table");

		lua_getfield(L, -1, "width");

		cout << "width from lua = " << lua_tonumberx(L, -2, nullptr) << endl;

		int windowWidth = 800, windowHeight = 600;

//		glutInit(&argc, argv);
//		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//		glutInitWindowSize(windowWidth, windowHeight);
//		glutCreateWindow("Jupiter game player");
//
//		glutReshapeFunc(reshape);
//		glutDisplayFunc(display);
//		glutIdleFunc(display);
//
//		if (glewInit() != GLEW_OK) throw runtime_error("glew init error");
//
//		glutMainLoop();

		lua_close(L);

		return EXIT_SUCCESS;
	}
	catch ( std::exception const & e )
	{
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
}


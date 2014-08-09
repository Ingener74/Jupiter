/*
 * DrawEngine.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: pavel
 */

#include <Jupiter/JupiterError.h>
#include <Jupiter/DrawEngine.h>

namespace jupiter
{

using namespace std;

DrawEngine::DrawEngine(IShaderLoader::Ptr sl, const glm::mat4& ortho, int screenW, int screenH)
{
    _program = createProgram(sl->getVertexShader(), sl->getFragmentShader());

    _uMVP = glGetUniformLocation(_program, "uMVP");
    _aPOS = glGetAttribLocation(_program, "aPOS");
    _aTEX = glGetAttribLocation(_program, "aTEX");
    _uTEX = glGetUniformLocation(_program, "uTEX");
}

DrawEngine::~DrawEngine()
{
    cout << "GLES20Engine::~GLES20Engine()" << endl;
    glDeleteProgram(_program);
    glDeleteShader(_vs);
    glDeleteShader(_fs);
}

void DrawEngine::setCurrentScene(Scene::Ptr)
{
	throw JupiterError("not implemented");
}

void DrawEngine::draw()
{
	throw JupiterError("not implemented");
}

void DrawEngine::inputToAll(int x, int y)
{
	throw JupiterError("not implemented");
}

void DrawEngine::animateAll(double elapsedMs)
{
	throw JupiterError("not implemented");
}

GLuint DrawEngine::createProgram(string vertexShader, string fragmentShader)
{
	GLuint _vs = createShader(GL_VERTEX_SHADER, vertexShader);
	GLuint _fs = createShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLuint program = glCreateProgram();
	if (!program) throw JupiterError("can't create program");

	glAttachShader(program, _vs);
	glAttachShader(program, _fs);

	glLinkProgram(program);
	GLint linkStatus = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus != GL_TRUE)
	{
		GLint bufLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
		if (bufLen)
		{
			vector<char> buf(bufLen);
			glGetProgramInfoLog(program, bufLen, NULL, &buf.front());
			throw JupiterError(&buf.front());
		}
	}

	glDeleteShader(_vs);
	glDeleteShader(_fs);

	return program;
}

GLuint DrawEngine::createShader(GLenum shaderType, string source)
{
	GLuint shader = glCreateShader(shaderType);
	if (!shader) throw JupiterError("can't create shader");

	const char* source_buffer = source.c_str();

	glShaderSource(shader, 1, &source_buffer, 0);
	glCompileShader(shader);

	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled) return shader;

	GLint infoLen = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
	if (!infoLen) throw JupiterError("error in create shader");

	vector<char> buf(infoLen);
	glGetShaderInfoLog(shader, infoLen, 0, &buf.front());

	throw JupiterError(&buf.front());
}

}  // namespace jupiter


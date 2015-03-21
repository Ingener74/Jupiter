
#if defined(SWIGPYTHON)
    %module PyJupiter
#elif defined(SWIGLUA)
    %module LuaJupiter
#else
    #warning no tupemaps
#endif

%{

#include "Jupiter/JupiterError.h"
#include "Jupiter/LinuxFileFactory.h"
#include "Jupiter/File.h"
#include "Jupiter/Game.h"
#include "Jupiter/JsonGame.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/Node.h"
#include "Jupiter/Controller.h"
#include "Jupiter/Image.h"
#include "Jupiter/PngImage.h"
#include "Jupiter/Texture.h"
#include "Jupiter/ImageTexture.h"
#include "Jupiter/Shader.h"
#include "Jupiter/FileShader.h"

using namespace jupiter;

%}

%include "std_string.i"
%include "std_vector.i"

%include "Jupiter/JupiterError.h"

%include "Jupiter/File.h"
%include "Jupiter/LinuxFileFactory.h"

%include "Jupiter/Game.h"
%include "Jupiter/JsonGame.h"

%include "Jupiter/Node.h"

%include "Jupiter/Sprite.h"

%include "Jupiter/Controller.h"

%include "Jupiter/Texture.h"
%include "Jupiter/ImageTexture.h"

%include "Jupiter/Image.h"
%include "Jupiter/PngImage.h"

%include "Jupiter/Shader.h"
%include "Jupiter/FileShader.h"
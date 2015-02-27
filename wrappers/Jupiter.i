
#if defined(SWIGPYTHON)
    %module(directors="1") PyJupiter
#elif defined(SWIGLUA)
    %module(directors="1") LuaJupiter
#else
    #warning no tupemaps
#endif

%{

#include "Jupiter/LinuxFileFactory.h"
#include "Jupiter/File.h"
#include "Jupiter/Game.h"
#include "Jupiter/JsonGame.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/Node.h"
#include "Jupiter/Controller.h"
#include "Jupiter/Image.h"
#include "Jupiter/JupiterError.h"
#include "Jupiter/Texture.h"

using namespace jupiter;

%}

%include "std_string.i"
%include "std_vector.i"

%feature("director") Controller;

%include "src/Aware.i"
%include "src/File.i"
%include "src/LinuxFileFactory.i"
%include "src/Game.i"
%include "src/JsonGame.i"
%include "src/Node.i"
%include "src/Sprite.i"
%include "src/Controller.i"
%include "src/JupiterError.i"
%include "src/Shape.i"
%include "src/Texture.i"
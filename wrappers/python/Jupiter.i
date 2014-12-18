
%module Jupiter
%{

#include <Jupiter/facade/Game.h>
#include <Jupiter/facade/Sprite.h>
#include <Jupiter/facade/Node.h>
#include <Jupiter/facade/Controller.h>
#include <Jupiter/Image.h>
#include <Jupiter/JupiterError.h>
#include <Jupiter/Texture.h>

using namespace jupiter;

%}

%include "std_string.i"
%include "std_vector.i"

%include "src/JupiterError.i"
%include "src/Node.i"
%include "src/Sprite.i"
%include "src/Game.i"
%include "src/Controller.i"

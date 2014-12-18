
%module Jupiter
%{

#include <Jupiter/Game.h>
#include <Jupiter/Sprite.h>
#include <Jupiter/Node.h>
#include <Jupiter/Controller.h>
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

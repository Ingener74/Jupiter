
%module Jupiter
%{

#include <Jupiter/Shape.h>
#include <Jupiter/facade/Sprite.h>
#include <Jupiter/facade/Game.h>
using namespace jupiter;

%}

%include "std_string.i"
%include "std_vector.i"

%include <Jupiter/facade/Sprite.h>
%include <Jupiter/JupiterError.h>
%include <Jupiter/facade/Game.h>


%module Jupiter
%{

#include <Jupiter/Shape.h>
#include <Jupiter/facade/Sprite.h>
using namespace jupiter;

%}

%include "std_string.i"
%include "std_vector.i"

%include <Jupiter/facade/Sprite.h>
%include <Jupiter/Shape.h>

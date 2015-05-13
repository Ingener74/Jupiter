
#if defined(SWIGPYTHON)
    %module PyJupiter
#elif defined(SWIGLUA)
    %module LuaJupiter
#else
    #warning no tupemaps
#endif

%begin %{
#include <cmath>
%}

%{

#include "Jupiter.h"
using namespace jupiter;

%}

namespace jupiter{
    void initJupiter();
}

%include "std_string.i"
%include "std_vector.i"
%include "exception.i"

%include "Jupiter/JupiterError.h"

%include "Jupiter/File.h"
%include "Jupiter/FileFactory.h"

%include "Jupiter/Game.h"
// %include "Jupiter/JsonGame.h"

%include "Jupiter/Node.h"

%include "Jupiter/Sprite.h"

%include "Jupiter/Controller.h"

%include "Jupiter/Texture.h"
%include "Jupiter/ImageTexture.h"
%include "Jupiter/ImageShape.h"

%include "Jupiter/Image.h"
%include "Jupiter/PngImage.h"

%include "Jupiter/Shader.h"
%include "Jupiter/FileShader.h"

%include "Jupiter/RenderVisitor.h"
%include "Jupiter/PrintVisitor.h"

%include "Jupiter/Camera.h"

%exception{
    try {
        %action
    } catch (JupiterError const& e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch (...) {
        SWIG_exception(SWIG_UnknownError, "Unknown error");
    }
}

#if defined(SWIGPYTHON)
    %module(directors="1") JupiterPython
#elif defined(SWIGLUA)
    %module(directors="1") JupiterLua
#elif defined(SWIGJAVA)
    %module(directors="1") JupiterJava
#else
    #warning no tupemaps
#endif

#if !defined(SWIGJAVA)
%begin %{
#include <cmath>
%}
#endif

// #pragma SWIG nowarn=362

// Sprite.h(31) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Sprite.h(42) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Transform.h(37) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Transform.h(38) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Camera.h(54) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Camera.h(56) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Body.h(37) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Body.h(39) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// Body.h(41) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// VisualBody.h(26) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// VisualBody.h(28) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
// VisualBody.h(30) : Warning 822: Covariant return types not supported in Java. Proxy method will return jupiter::Node *.
#pragma SWIG nowarn=822

// NodeVisitor.h(63) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'
// RenderVisitor.h(55) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'
// PrintVisitor.h(28) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'
// Physics.h(33) : Warning 314: 'end' is a Lua keyword, renaming to 'c_end'
#pragma SWIG nowarn=314

%{
#include "Jupiter.h"
using namespace jupiter;
%}

%include std_string.i
%include std_vector.i
%include exception.i
%exception{
    try {
        $action
    } catch (JupiterError const& e) {
        // std::cout << e.what() << std::endl;
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch (std::exception const& e) {
        SWIG_exception(SWIG_RuntimeError, (std::string("std::exception: ") + e.what()).c_str());
    } catch (...) {
        SWIG_exception(SWIG_UnknownError, "Unknown error");
    }
}

%feature("ref")   RCO "$this->addRef();"
%feature("unref") RCO "$this->removeRef();"

%include "Jupiter.h"

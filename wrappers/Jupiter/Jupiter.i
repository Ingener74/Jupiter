
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

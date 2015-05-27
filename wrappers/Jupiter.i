
#if defined(SWIGPYTHON)
    %module(directors="1") JupiterPython
#elif defined(SWIGLUA)
    %module(directors="1") JupiterLua
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

%include "Jupiter.h"


%module(directors="1") NextSummerPython

%begin %{
#include <cmath>
%}

%{
#include "NextSummer.h"
using namespace nextsummer;
%}

%include std_string.i
%include exception.i
%exception{
    try {
        $action
    } catch (std::exception const& e) {
        SWIG_exception(SWIG_RuntimeError, (std::string("std::exception: ") + e.what()).c_str());
    } catch (...) {
        SWIG_exception(SWIG_UnknownError, "Unknown error");
    }
}

%include "NextSummer.h"


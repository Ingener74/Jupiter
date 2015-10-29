
#if defined(SWIGPYTHON)
    %module glmPython
#elif defined(SWIGLUA)
    %module glmLua
#else
    #warning no tupemaps
#endif

%begin %{
#include <cmath>
%}

// type_vec3.hpp:83: Warning 312: Nested union not currently supported (ignored).
// type_vec3.hpp:84: Warning 312: Nested union not currently supported (ignored).
// type_vec3.hpp:85: Warning 312: Nested union not currently supported (ignored).
// type_vec3.hpp:106: Warning 389: operator[] ignored (consider using %extend)
// type_vec3.hpp:107: Warning 389: operator[] ignored (consider using %extend)
// type_vec3.hpp:177: Warning 362: operator= ignored
// type_vec3.hpp:180: Warning 362: operator= ignored
// type_vec3.hpp:208: Warning 383: operator++ ignored
// type_vec3.hpp:209: Warning 384: operator-- ignored
// type_vec3.hpp:210: Warning 383: operator++ ignored
// type_vec3.hpp:211: Warning 384: operator-- ignored
// setup.hpp:960: Warning 315: Nothing known about 'std::size_t'.
#pragma SWIG nowarn=315,312,389,362,383,384

%{
#include <glm/glm.hpp>
%}

%include <glm/detail/setup.hpp>
%include <glm/detail/type_vec3.hpp>

// %template(glm::vec3) glm::tvec3<float, glm::highp>;

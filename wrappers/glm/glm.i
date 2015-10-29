
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

%{
#include <glm/glm.hpp>
%}

%include <glm/detail/setup.hpp>
%include <glm/detail/type_vec3.hpp>

// %template(glm::vec3) glm::tvec3<float, glm::highp>;

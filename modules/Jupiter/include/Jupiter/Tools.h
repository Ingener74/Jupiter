/*
 * Tools.h
 *
 *  Created on: May 25, 2014
 *      Author: ingener
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#ifdef SWIG
#else
    #include <memory>
    #include <utility>
    #include <iostream>
    #include <string>

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/quaternion.hpp>

    #include "Jupiter/JupiterError.h"
#endif

namespace jupiter {

template<typename T, typename ... Args>
std::unique_ptr<T> make_unique_(Args ... args) {
    std::unique_ptr<T> ptr(new T(std::forward<Args>(args)...));
    return ptr;
}


template<typename T> std::string to_string(const T& n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

std::ostream& operator<<(std::ostream& out, const glm::mat4& r);
std::ostream& operator<<(std::ostream& out, const glm::vec3& r);
std::ostream& operator<<(std::ostream& out, const glm::quat& r);

class Tools {
public:
    Tools() = delete;
    virtual ~Tools() = delete;

    static uint32_t upperPowerOfTwo(uint32_t v);
    static void glError(const std::string& file = {}, int line = -1, const std::string& function = {});
};

//#define CHECK_GL_ERROR Tools::glError(__FILE__, __LINE__, __FUNCTION__);
#define CHECK_GL_ERROR

} /* namespace ndk_game */

#endif /* TOOLS_H_ */

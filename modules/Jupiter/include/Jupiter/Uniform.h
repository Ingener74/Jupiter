/*
 * Uniform.h
 *
 *  Created on: Mar 23, 2015
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_UNIFORM_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_UNIFORM_H_

#ifdef SWIG
    namespace jupiter {
        #pragma SWIG nowarn=509
    }  // namespace jupiter
#else
    #include <string>

    #include <GL/glew.h>

    #define GLM_FORCE_RADIANS
    #include <glm/glm.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>
#endif

namespace jupiter {

class Uniform {
public:
    Uniform(const std::string& name, int uniform);
    virtual ~Uniform();

    void set(int);
    void set(int, int);
    void set(int, int, int);
    void set(int, int, int, int);

    void set(float);
    void set(float, float);
    void set(float, float, float);
    void set(float, float, float, float);

    void set(const glm::mat4x4& matrix, bool transpose = false);

    void set(const class Texture* texture);

private:
    std::string name;
    int uniform;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_UNIFORM_H_ */

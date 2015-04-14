/*
 * Program.h
 *
 *  Created on: Apr 14, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_V2_PROGRAM_H_
#define APPS_TEST_V2_PROGRAM_H_

#include <string>
#include <vector>

#define GLM_FORCE_RADIAN
#include <glm/glm.hpp>

#include "Attribute.h"
#include "Uniform.h"

class Program {
public:
    Program(const std::string& vertesShader, const std::string& fragmentShader);
    virtual ~Program();

    const Attribute& getAttribute(const std::string& attributeName) const;
    void setUniformMatrix4x4(const std::string& uniformName, const glm::mat4& matrix);

    friend std::ostream& operator<<(std::ostream& out, const Program& r);

protected:
    GLuint program = 0;
    std::vector<Attribute> attributes;
    std::vector<Uniform> uniforms;
};

#endif /* APPS_TEST_V2_PROGRAM_H_ */

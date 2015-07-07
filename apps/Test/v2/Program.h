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

    void use();

    const Attribute& getAttribute(const std::string& attributeName) const;
    const Uniform& getUniform(const std::string& uniformName) const;

    void setUniform(const std::string& uniformName, GLuint uniformData);
    void setUniform(GLuint uniformName, GLuint uniformData);
    void setUniform(const Uniform& uniform, GLuint uniformData);

    void setUniformMatrix4x4(const std::string& uniformName, const glm::mat4& matrix);

    friend std::ostream& operator<<(std::ostream& out, const Program& r);

    GLuint getProgram() const;
    void setProgram(GLuint program = 0);

    GLint getAttribute_(const std::string& name) const;
    GLint getUniform_(const std::string& name) const;

protected:
    GLuint program = 0;

    std::vector<Attribute> attributes;
    std::vector<Uniform> uniforms;
};

inline GLuint Program::getProgram() const {
    return program;
}

inline void Program::setProgram(GLuint program) {
    this->program = program;
}

inline GLint Program::getAttribute_(const std::string& name) const {
    glGetAttribLocation(program, name.c_str());
}

inline GLint Program::getUniform_(const std::string& name) const {
    glGetUniformLocation(program, name.c_str());
}

#endif /* APPS_TEST_V2_PROGRAM_H_ */

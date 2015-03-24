/*
 * VertexComponent.h
 *
 *  Created on: Mar 24, 2015
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_VERTEXCOMPONENT_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_VERTEXCOMPONENT_H_

#include <cstdint>

namespace jupiter {

class VertexComponent {
public:
    VertexComponent(uint32_t size = 0, float* offset = nullptr);
    virtual ~VertexComponent();

    uint32_t getSize() const;
    const float* getOffset() const;

private:
    uint32_t size = 0;
    float* offset = nullptr;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_VERTEXCOMPONENT_H_ */

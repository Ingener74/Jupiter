/*
 * VisualBody.h
 *
 *  Created on: Jun 16, 2015
 *      Author: pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_VISUALBODY_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_VISUALBODY_H_

#ifdef SWIG
#else
#endif

#include "Shader.h"
#include "Node.h"

namespace jupiter {

class VisualBody: public Node {
public:
    VisualBody(Shader*);
    virtual ~VisualBody();

    VisualBody* setProgram(Shader*);
    Shader* getProgram();

private:
    Ref<Shader> _shader;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_VISUALBODY_H_ */

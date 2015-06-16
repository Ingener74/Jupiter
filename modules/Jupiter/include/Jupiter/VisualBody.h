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
    #include "Ref.h"
#endif

#include "Shader.h"
#include "Body.h"

namespace jupiter {

class VisualBody: public Body {
public:
    VisualBody(Physics*, b2BodyDef, PhysicsShape*);
    virtual ~VisualBody();

    VisualBody* setProgram(Shader*);
    Shader* getProgram();

private:
    Ref<Shader> _shader;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_VISUALBODY_H_ */

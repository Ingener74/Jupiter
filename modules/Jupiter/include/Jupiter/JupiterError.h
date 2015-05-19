/*
 * JupiterError.h
 *
 *  Created on: Aug 7, 2014
 *      Author: pavel
 */

#ifndef JUPITERERROR_H_
#define JUPITERERROR_H_

#ifdef SWIG
    #pragma SWIG nowarn=401
#else
    #include <stdlib.h>
    #include <sstream>
    #include <stdexcept>
    #include <string>

    #include "Tools.h"
    namespace jupiter {
        #define jassert(condition, message) \
            if(!(condition)) \
                throw JupiterError(std::string(__FILE__) + ": " + to_string(__LINE__) + ": " + std::string(__PRETTY_FUNCTION__) + ": " + message)
    }
#endif

namespace jupiter
{

class JupiterError: public std::runtime_error
{
public:
    JupiterError(const std::string& message = "Jupiter error") :
            std::runtime_error(message + backtrace())
    {
    }

    virtual ~JupiterError() throw () = default;

protected:
    static std::string backtrace();
};



}  // namespace jupiter

#endif /* JUPITERERROR_H_ */

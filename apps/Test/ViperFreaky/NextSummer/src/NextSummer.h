/*
 * NextSummer.h
 *
 *  Created on: Oct 16, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_VIPERFREAKY_NEXTSUMMER_NEXTSUMMER_H_
#define APPS_TEST_VIPERFREAKY_NEXTSUMMER_NEXTSUMMER_H_

#include <string>

namespace nextsummer {

class NextSummer {
public:
    NextSummer(std::string const&);
    virtual ~NextSummer();

    void sayHelloNextSummer();

    void execPythonScript(std::string const& script);

private:
    std::string _s;
    static int _i;
};

} /* namespace nextsummer */

#endif /* APPS_TEST_VIPERFREAKY_NEXTSUMMER_NEXTSUMMER_H_ */

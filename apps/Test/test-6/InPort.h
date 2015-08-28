/*
 * InPort.h
 *
 *  Created on: Aug 28, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_TEST_6_INPORT_H_
#define APPS_TEST_TEST_6_INPORT_H_

#include <map>
#include <string>

class In;

class InPort {
public:
    InPort();
    virtual ~InPort();

    In* in(const std::string& name);

private:
    std::map<std::string, In*> _ins;
};

#endif /* APPS_TEST_TEST_6_INPORT_H_ */

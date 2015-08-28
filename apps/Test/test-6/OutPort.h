/*
 * OutPort.h
 *
 *  Created on: Aug 28, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_TEST_6_OUTPORT_H_
#define APPS_TEST_TEST_6_OUTPORT_H_

#include <string>
#include <map>

class In;

class OutPort {
public:
    OutPort();
    virtual ~OutPort();

    void out(const std::string& name, In*);

private:
    std::map<std::string, In*> _ins;
};

#endif /* APPS_TEST_TEST_6_OUTPORT_H_ */

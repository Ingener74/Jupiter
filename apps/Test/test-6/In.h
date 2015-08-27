/*
 * In.h
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_TEST_6_IN_H_
#define APPS_TEST_TEST_6_IN_H_

#include <list>

class In {
public:
    friend class Out;
    In();
    virtual ~In();

    void update();

private:
    void outOff(Out*);

    Out* _out;
};

#endif /* APPS_TEST_TEST_6_IN_H_ */

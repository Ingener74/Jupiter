/*
 * Out.h
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_TEST_6_OUT_H_
#define APPS_TEST_TEST_6_OUT_H_

#include <list>

class In;

class Out {
public:
    Out();
    virtual ~Out();

    template<typename Data>
    Data* getData(){
    }

    void add(In* in);
    void remove(In* in);

protected:
    void notify();
    std::list<In*> _ins;
};

#endif /* APPS_TEST_TEST_6_OUT_H_ */

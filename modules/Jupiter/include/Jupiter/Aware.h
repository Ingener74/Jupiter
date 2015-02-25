/*
 * Aware.h
 *
 *  Created on: Feb 10, 2015
 *      Author: pavel
 */

#ifndef AWARE_H_
#define AWARE_H_

#include <map>
#include <string>
#include <utility>
#include <iostream>

#include "Jupiter/JupiterError.h"

namespace jupiter {

class Object {
public:
    Object(const std::string& name = { });
    virtual ~Object();

    virtual void setName(const std::string& name);
    virtual const std::string& getName() const;

private:
    std::string name;
};

class Aware // In honor of the film's "Virus" 1999
{
public:
    Aware() = delete;
    virtual ~Aware() = delete;

    static void add(Object*);
    static void remove(Object*);
    static size_t objectsCount();

    template<typename T, typename ... Args>
    static T* create(Args... args) {
        T* o = new T(args...);

        add(o, true);

        return o;
    }

    template<typename T>
    static T* get(const std::string& name) {
        auto r = dynamic_cast<T*>(Register() [ name ].second);
        if (!r)
            throw JupiterError("Aware can't cast " + name);
        return r;
    }

    static void release();

private:
    using Created = bool;
    using Reg = std::map<std::string, std::pair<Created, Object*>>;
    static Reg& Register();

    static void add(Object*, Created);
};

} /* namespace jupiter */

#endif /* AWARE_H_ */

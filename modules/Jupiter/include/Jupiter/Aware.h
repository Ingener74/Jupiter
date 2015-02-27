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

    static int objects;

protected:
    std::string name;
};

class Aware // In honor of the film's "Virus" 1999
{
public:
    friend class Object;

    Aware() = delete;
    virtual ~Aware() = delete;

    template<typename T, typename ... Args>
    static T* create(Args ... args) {
        T* o = new T(args...);

        setCreated(o);

        return o;
    }

    template<typename T>
    static T* get(const std::string& name) {
        auto it = Register().find(name);
        if (it == Register().end())
            return nullptr;
        auto r = dynamic_cast<T*>(Register() [ name ].second);
        if (!r)
            throw JupiterError("Aware can't cast " + name);
        return r;
    }

    static size_t objectsCount();
    static void release();

private:
    using Created = bool;
    using AwareObject = std::pair<Created, Object*>;
    using Name = std::string;
    using Reg = std::map<Name, AwareObject>;

    static Reg& Register();

    static void add(Object*);
    static void remove(Object*);
    static void setCreated(Object*);
};

} /* namespace jupiter */

#endif /* AWARE_H_ */

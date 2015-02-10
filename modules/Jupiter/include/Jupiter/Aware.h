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

#include "Jupiter/JupiterError.h"

namespace jupiter
{

class Aware // In honor of the film's "Virus" 1999
{
public:
    class Object
    {
    public:
        Object(const std::string& name = {});
        virtual ~Object() = default;

        virtual void setName(const std::string& name);
        virtual const std::string& getName() const;

    private:
        std::string name;
    };

    Aware() = delete;
    virtual ~Aware() = delete;

    static void add(Object* so);
    static void remove(Object* so);

    template<typename T>
    static T* get(const std::string& name)
    {
        auto r = dynamic_cast<T*>(Register()[name]);
        if(!r)
            throw JupiterError("Aware can't cast " + name);
        return r;
    }

private:
    using Reg = std::map<std::string, Object*>;
    static Reg& Register();
};

} /* namespace jupiter */

#endif /* AWARE_H_ */

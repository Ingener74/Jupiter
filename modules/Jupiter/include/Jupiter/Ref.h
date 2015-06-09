/*
 * Ref.h
 *
 *  Created on: Jun 8, 2015
 *      Author: pavel
 */

#ifndef APPS_REF_REF_H_
#define APPS_REF_REF_H_

#include "RCO.h"
#include "JupiterError.h"

namespace jupiter {

template<typename T>
class Ref {
public:
    explicit Ref(T* ptr = nullptr);

    template<typename ... Args>
    explicit Ref(Args&& ... args);

    Ref(const Ref& r);
    Ref& operator=(const Ref& r);
    Ref& operator=(T* r);

    virtual ~Ref();

    T* get();
    T* operator ->();

    operator bool() const;

private:
    T* _ptr = nullptr;
};

}  // namespace jupiter

#endif /* APPS_REF_REF_H_ */

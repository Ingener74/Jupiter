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
//    static_assert(std::is_base_of<RCO, T>::value, "It does not inherit from RCO");

    explicit Ref(T* ptr = nullptr) :
        _ptr(ptr) {
        if (_ptr)
            _ptr->addRef();
    }

    template<typename ... Args>
    explicit Ref(Args&& ... args) {
        _ptr = new T(std::forward<Args>(args)...);
        _ptr->addRef();
    }

    Ref(const Ref& r) {
        *this = r;
    }

    Ref& operator=(const Ref& r) {
        return *this = const_cast<Ref&>(r).get();
    }

    Ref& operator=(T* r) {
        if (_ptr)
            _ptr->removeRef();
        _ptr = r;
        if (_ptr)
            _ptr->addRef();
    }

    virtual ~Ref() {
        if (_ptr)
            _ptr->removeRef();
    }

    T* get() {
        jassert(_ptr, "no ptr");
        return _ptr;
    }

    T* operator ->() {
        return get();
    }

    operator bool() const {
        return _ptr;
    }

private:
    T* _ptr = nullptr;
};

}  // namespace jupiter

#endif /* APPS_REF_REF_H_ */

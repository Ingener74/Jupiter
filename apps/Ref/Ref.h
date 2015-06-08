/*
 * Ref.h
 *
 *  Created on: Jun 8, 2015
 *      Author: pavel
 */

#ifndef APPS_REF_REF_H_
#define APPS_REF_REF_H_

#include "RCO.h"

template<typename T>
class Ref {
public:
    static_assert(std::is_base_of<RCO, T>::value, "It does not inherit from RCO");

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
        if (_ptr)
            _ptr->removeRef();
        _ptr = r._ptr;
        if (_ptr)
            _ptr->addRef();
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
        if (!_ptr)
            throw std::runtime_error("reference is invalid");
        return _ptr;
    }

    T* operator ->() {
        return get();
    }

private:
    T* _ptr = nullptr;
};

#endif /* APPS_REF_REF_H_ */

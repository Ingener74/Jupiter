#ifndef __RCO_H__
#define __RCO_H__

#include <iostream>

#define log std::cout << __PRETTY_FUNCTION__ << " " << _counter << std::endl;

class RCO {
public:
    RCO();
    virtual ~RCO();

    void addRef();
    void removeRef();

    int refCount() const;

    static int objects();

private:
    int _counter = 0;
    static int _objects;
};

inline RCO::RCO() {
    log
    ++_objects;
}

inline RCO::~RCO() {
    log
    --_objects;
}

inline void RCO::addRef() {
    ++_counter;
    log
}

inline void RCO::removeRef() {
    --_counter;
    log
    if (_counter == 0)
        delete this;
}

inline int RCO::refCount() const {
    return _counter;
}

inline int RCO::objects() {
    return _objects;
}

#endif /* __RCO_H__ */


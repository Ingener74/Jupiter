#ifndef __RCO_H__
#define __RCO_H__

#ifdef SWIG
#else
    #include <iostream>
#endif

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
    std::cout << __PRETTY_FUNCTION__ << " " << _counter << std::endl;
    ++_objects;
}

inline RCO::~RCO() {
    std::cout << __PRETTY_FUNCTION__ << " " << _counter << std::endl;
    --_objects;
}

inline void RCO::addRef() {
    ++_counter;
    std::cout << __PRETTY_FUNCTION__ << " " << _counter << std::endl;
}

inline void RCO::removeRef() {
    --_counter;
    std::cout << __PRETTY_FUNCTION__ << " " << _counter << std::endl;
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


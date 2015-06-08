#include <iostream>

#include "RCO.h"

using namespace std;

#define log cout << __PRETTY_FUNCTION__ << " " << _counter << endl;

int RCO::_objects = 0;

RCO::RCO() {
    log
    ++_objects;
}

RCO::~RCO() {
    log
    --_objects;
}

void RCO::addRef() {
    ++_counter;
    log
}

void RCO::removeRef() {
    --_counter;
    log
    if (_counter == 0)
        delete this;
}

int RCO::refCount() const {
    return _counter;
}

int RCO::objects() {
    return _objects;
}

#include <iostream>

#include "RCO.h"

using namespace std;

#define log cout << __PRETTY_FUNCTION__ << " " << _counter << endl;

RCO::RCO() {
    log
}

RCO::~RCO() {
    log
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


#include <iostream>

#include "RCO.h"

using namespace std;

#define log cout << __func__ << " " << _counter << endl;

RCO::RCO(){
    log
}

RCO::~RCO(){
    log
}

void RCO::addRef(){
    _counter++;
    log
}

void RCO::removeRef(){
    log
    if(!--_counter){
        delete this;
    }
}

int RCO::refCount() const {
    return _counter;
}

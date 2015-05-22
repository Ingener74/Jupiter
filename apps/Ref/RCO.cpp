
#include <iostream>

#include "RCO.h"

using namespace std;

RCO::RCO(){
    cout << __func__ << " " << _counter << endl;
}

RCO::~RCO(){
    cout << __func__ << " " << _counter << endl;
}

void RCO::addRef(){
    cout << __func__ << " " << _counter << endl;
    _counter++;
}

void RCO::removeRef(){
    cout << __func__ << " " << _counter << endl;
    if(!--_counter){
        delete this;
    }
}

int RCO::refCount() const {
    return _counter;
}

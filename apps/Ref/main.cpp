/*
 * main.cpp
 *
 *  Created on: May 15, 2015
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

#include "RCO.h"

using namespace std;

class Ref {
public:
    Ref(RCO* r = nullptr): _rco(r){
        if (_rco)
            _rco->addRef();
    }
//    Ref(const Ref& ref) {
//        *this = ref;
//    }
    Ref(const Ref& ref){
        if(_rco)
            _rco->removeRef();
        _rco = ref._rco;
        if(_rco)
            _rco->addRef();
    }
    virtual ~Ref() {
        if (_rco)
            _rco->removeRef();
    }

    friend ostream& operator<<(ostream& o, const Ref& r) {
        return o << "Ref{" << r._rco->refCount() << "}";
    }

private:
    RCO* _rco = nullptr;
};

class Test: public RCO {
public:
    Test() {
        cout << __func__ << " " << endl;
    }
    virtual ~Test() {
        cout << __func__ << " " << endl;
    }
};

class RcoUser{
public:
    RcoUser(){
    }
    virtual ~RcoUser(){
    }
    
    void testRco(RCO* rco){
        _rco = Ref(rco);
    }
    
private:
    Ref _rco;
};

int main(int argc, char **argv) {
    try {
        Ref t1{new Test};

        auto  t2 = t1;

        auto t3 = t2;

        cout << t1 << endl;
        cout << t2 << endl;
        cout << t3 << endl;
        
//        RcoUser t5;
//        t5.testRco(new Test);

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}


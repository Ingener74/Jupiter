/*
 * test-6.cpp
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#include <iostream>

using namespace std;

#include "OutPort.h"
#include "InPort.h"

class Numbers: public OutPort {
public:
    Numbers() {
    }
    virtual ~Numbers() {
    }
};

class Strings: public InPort, public OutPort {
public:
    Strings() {
    }
    virtual ~Strings() {
    }
};

class Files: public InPort {
public:
    Files() {
    }
    virtual ~Files() {
    }
};

int main(int argc, char **argv) {
    try {

        Numbers n;

        Strings s;
        n.out("numbers", s.in("numbers"));

        Files f;
        s.out("strings", f.in("strings"));

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}


/*
 * main.cpp
 *
 *  Created on: May 15, 2015
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

#include "Ref.h"

using namespace std;

class Test: public RCO {
public:
    Test(string str, float f) :
        _str(str), _f(f) {
    }
    virtual ~Test() {
    }

    void test() {
        cout << _str << " " << _f << endl;
    }

private:
    string _str;
    float _f;
};

class RcoUser {
public:
    RcoUser() {
    }
    virtual ~RcoUser() {
    }

    void testRco(Test* rco) {
        _rco = rco;

        _rco->test();
    }

private:
    Ref<Test> _rco;
};

void foo(Test* t) {
    Ref<Test> { t };
    t->test();
}

int main(int argc, char **argv) {
    try {
        {
            Ref<Test> t1 { "Pi", 3.1415 };

            auto t2 = t1;

            auto t3 = t2;

            t3->test();

            foo(new Test{"Foo", 42});

            RcoUser t5;
            t5.testRco(new Test { "Euler", 2.72 });
            cout << "objects " << RCO::objects() << endl;
        }
        cout << "objects " << RCO::objects() << endl;
    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}


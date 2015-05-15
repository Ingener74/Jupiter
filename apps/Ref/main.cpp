/*
 * main.cpp
 *
 *  Created on: May 15, 2015
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Ref {
public:

    template<typename ... Args>
    Ref(Args&&... args) {
        core = new Core;
        core->counter++;
        core->data = new T(args...);
    }
    Ref(const Ref& r) {
        *this = r;
    }
    Ref& operator=(const Ref& r) {
        core = r.core;
        core->counter++;
        return *this;
    }
    virtual ~Ref() {
        if (!core->counter--) {
            delete core->data;
            delete core;
        }
    }

    friend ostream& operator<<(ostream& o, const Ref& r) {
        return o << "Ref{" << r.core->counter << "}";
    }

private:
    struct Core {
        T* data = nullptr;
        int counter = 0;
    };
    Core* core = nullptr;
};

class Test {
public:
    Test() {
    }
    virtual ~Test() {
    }
};

int main(int argc, char **argv) {
    try {
        Ref<Test> t1{};

        auto  t2 = t1;

        auto t3 = t2;

        cout << t1 << endl;
        cout << t2 << endl;
        cout << t3 << endl;

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}


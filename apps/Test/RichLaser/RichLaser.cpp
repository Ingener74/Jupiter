/*
 * RichLaser.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: pavel
 */

#include <iostream>
#include <vector>

using namespace std;

class OutputBuffer: public streambuf {
public:
    OutputBuffer() :
        _buffer(1 << 8) {
        setp(_buffer.data(), _buffer.data() + _buffer.size());
    }
    virtual ~OutputBuffer() {
    }

    virtual int sync() {
        printf("%s", _buffer.data()); // output
        for(auto& i: _buffer) i = 0; // clean
        setp(_buffer.data(), _buffer.data() + _buffer.size()); // reset
        return 0;
    }

private:
    vector<char> _buffer;
};

OutputBuffer outbuf;
ostream out { &outbuf };

int main(int argc, char **argv) {
    cout << "RichLaser" << endl;

    out << "foo " << 42 << endl;
    out << "quz ";
    out << "bar" << endl;
}


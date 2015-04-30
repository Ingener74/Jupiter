/*
 * JupiterError-linux.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: pavel
 */

#include <execinfo.h>

#include "Jupiter/JupiterError.h"

namespace jupiter {

using namespace std;

string JupiterError::backtrace() {
    const int buffer_size = 1000;
    void *buffer[buffer_size];
    int n = ::backtrace(buffer, buffer_size);

    char** strings = backtrace_symbols(buffer, n);
    if (strings == nullptr)
        return string("i can't print stack trace");

    stringstream res;
    res << endl << "Call stack" << endl;
    for (int i = 2; i < n; ++i) {
        res << i << ": " << strings[i] << endl;
    }
    free(strings);
    return res.str();
}

}  // namespace jupiter

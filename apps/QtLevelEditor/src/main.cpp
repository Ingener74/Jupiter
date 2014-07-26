/*
 * main.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#include <iostream>
#include <stdexcept>

using namespace std;

int main( int argc, char **argv )
{
    try
    {

    }
    catch ( exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}


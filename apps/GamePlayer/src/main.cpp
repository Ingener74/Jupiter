/*
 * main.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

using namespace std;

int main( int argc, char **argv )
{
	try
	{
		cout << "Game player" << endl;
	}
	catch ( exception const & e )
	{
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}


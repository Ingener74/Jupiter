/*
 * main.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: pavel
 */

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	try
	{
		cout << "Parse lua test" << endl;



		return 0;
	}
	catch ( std::exception const & e )
	{
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
}


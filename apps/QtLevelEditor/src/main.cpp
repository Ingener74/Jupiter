/*
 * main.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#include <LevelEditor.h>

using namespace std;

shared_ptr<QApplication> app;

int main( int argc, char **argv )
{
	try
	{
		app = make_shared<QApplication>( argc, argv );

		LevelEditor le( app );
		le.show();

		return app->exec();
	}
	catch ( exception const & e )
	{
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}


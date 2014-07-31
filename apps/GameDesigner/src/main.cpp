/*
 * main.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#include <GameDesigner.h>

using namespace std;

shared_ptr<QApplication> app;

int main( int argc, char **argv )
{
	try
	{
		app = make_shared<QApplication>( argc, argv );

		GameDesigner gd( app );
		gd.show();

		return app->exec();
	}
	catch ( exception const & e )
	{
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}


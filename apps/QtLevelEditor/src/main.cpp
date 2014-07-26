/*
 * main.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#include <iostream>
#include <stdexcept>

#include <QtWidgets/qapplication.h>

using namespace std;

int main( int argc, char **argv )
{
    try
    {
        cout << "Level editor" << endl;

        QApplication app(argc, argv);



        return app.exec();
    }
    catch ( exception const & e )
    {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}


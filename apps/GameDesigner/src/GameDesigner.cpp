/*
 * GameDesigner.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#include <GameDesigner.h>

using namespace std;

GameDesigner::GameDesigner( std::shared_ptr<QApplication> app, QWidget* parent ) :
		QMainWindow( parent )
{
	(_ui = make_shared<Ui_MainWindow>())->setupUi( this );
}

GameDesigner::~GameDesigner()
{
}


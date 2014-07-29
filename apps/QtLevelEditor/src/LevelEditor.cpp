/*
 * LevelEditor.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#include <LevelEditor.h>

using namespace std;

LevelEditor::LevelEditor( std::shared_ptr<QApplication> app, QWidget* parent ) :
		QMainWindow( parent )
{
	(_ui = make_shared<Ui_MainWindow>())->setupUi( this );
}

LevelEditor::~LevelEditor()
{
}


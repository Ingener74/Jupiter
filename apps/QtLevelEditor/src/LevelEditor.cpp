/*
 * LevelEditor.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#include <LevelEditor.h>

using namespace std;

LevelEditor::LevelEditor( QWidget* parent ) :
        QMainWindow(parent)
{
    _ui = make_shared<Ui_MainWindow>();
    _ui->setupUi(this);
}

LevelEditor::~LevelEditor()
{
}


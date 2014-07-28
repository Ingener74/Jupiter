/*
 * LevelEditor.h
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#ifndef LEVELEDITOR_H_
#define LEVELEDITOR_H_

#include <Common.h>

#include <ui_QtLevelEditor.h>

class LevelEditor: public QMainWindow
{
    Q_OBJECT
public:
    LevelEditor( QWidget* parent = nullptr );
    virtual ~LevelEditor();

private:
    std::shared_ptr<Ui_MainWindow> _ui;
};

#endif /* LEVELEDITOR_H_ */

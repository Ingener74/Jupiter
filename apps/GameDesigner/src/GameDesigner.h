/*
 * GameDesigner.h
 *
 *  Created on: Jul 27, 2014
 *      Author: ingener
 */

#ifndef LEVELEDITOR_H_
#define LEVELEDITOR_H_

#include <Common.h>

#include <ui_GameDesigner.h>

class GameDesigner: public QMainWindow
{
	Q_OBJECT
public:
	GameDesigner( std::shared_ptr<QApplication>, QWidget* parent = nullptr );
	virtual ~GameDesigner();

private:
	std::shared_ptr<Ui_MainWindow> _ui;
};

#endif /* LEVELEDITOR_H_ */

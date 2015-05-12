#!/usr/bin/env python
# encoding: utf-8

import sys
import subprocess
from PySide.QtGui import QApplication, QFileDialog, QMainWindow, QGroupBox, QLabel, QVBoxLayout, QHBoxLayout, QWidget,\
    QTextEdit
from PySide import QtCore

from prebuild import Linux, Downloader, Builder

class BoostBuilder(Builder):
    def __init__(self, downloader):
        super(BoostBuilder, self).__init__(downloader)
    
    def build(self):
        self.downloader.show()
        
        print 'after download'


class MainWindow(QWidget):
    MIN_SIZE = 600
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        
        test = QLabel(u'Test')
        envLayout = QVBoxLayout()
        envLayout.addWidget(test)
        
        environment = QGroupBox(u'Окружение')
        environment.setMinimumSize(self.MIN_SIZE, self.MIN_SIZE)
        environment.setLayout(envLayout)
        
        components = QGroupBox(u'Компоненты')
        components.setMinimumSize(self.MIN_SIZE, self.MIN_SIZE)
        
        horLayout = QHBoxLayout()
        horLayout.addWidget(environment)
        horLayout.addWidget(components)
        
        consoleEdit = QTextEdit()
        
        consoleLayout = QVBoxLayout()
        consoleLayout.addWidget(consoleEdit)
        
        console = QGroupBox(u'Консоль')
        console.setLayout(consoleLayout)
        
        verLayout = QVBoxLayout()
        verLayout.addLayout(horLayout)
        verLayout.addWidget(console)
        self.setLayout(verLayout)
        
        self.setWindowTitle(u'Сборка зависимостей')
    
    def keyPressEvent(self, e):
        if e.key() == QtCore.Qt.Key_Escape:
            raise SystemExit

def main():
    app = QApplication(sys.argv)
#     print QApplication.setStyle(u"plastique")
    
    mainWindow = MainWindow()
    mainWindow.show()
    
#     downloadDirectory = QFileDialog.getExistingDirectory(None, u'Укажи директорию для закачки файлов')
#     platform = Linux(downloadDirectory)
#     
#     boostBuilder = BoostBuilder(Downloader(u'Скачай последнюю версию библиотеки Boost', \
#                                            'http://sourceforge.net/projects/boost/files/boost/', platform))
#     boostBuilder.build()
    
    return app.exec_()


if __name__ == '__main__':
    main()

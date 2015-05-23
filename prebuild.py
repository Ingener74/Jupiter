#!/usr/bin/env python
# encoding: utf-8

import sys
import subprocess
from PySide.QtGui import QApplication, QFileDialog, QMainWindow, QGroupBox, QLabel, QVBoxLayout, QHBoxLayout, QWidget,\
    QTextEdit, QIcon, QPixmap
from PySide import QtCore

from prebuild import *

class BoostBuilder(Builder):
    def __init__(self, downloader):
        super(BoostBuilder, self).__init__(downloader)
    
    def build(self):
        self.downloader.show()
        
        print 'after download'


class MainWindow(QWidget, Ui_Main):
    MIN_SIZE = 600
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        
        
    def keyPressEvent(self, e):
        if e.key() == QtCore.Qt.Key_Escape:
            raise SystemExit


def setStyle():
    if sys.platform == 'win32':
        QApplication.setStyle(u"windows")
    elif sys.platform == 'linux2':
        QApplication.setStyle(u"plastique")
    else:
        print u'Неизвестная система'

def main():
    setStyle()
    app = QApplication(sys.argv)
    
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

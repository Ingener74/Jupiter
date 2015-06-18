#!/usr/bin/env python
# encoding: utf-8

import sys, os
import subprocess
from PySide.QtGui import (QApplication, QFileDialog, QWidget)

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

        '''
        '''

        myEnv = os.environ.copy()
        myEnv['PATH'] = 'C:\\cygwin64\\bin;' + myEnv['PATH']
        # print myEnv

        buildDirectory = '..'

        out, err = subprocess.Popen(['wget.exe', 'https://box2d.googlecode.com/files/Box2D_v2.3.0.7z', '-P', buildDirectory], stdout=subprocess.PIPE, env=myEnv).communicate()
        # output = proc.stdout.read()
        # print output

    def keyPressEvent(self, e):
        if e.key() == QtCore.Qt.Key_Escape:
            raise SystemExit

# noinspection PyPep8Naming
if __name__ == '__main__':
    QApplication.setStyle(u'plastique')
    app = QApplication(sys.argv)

    mainWindow = MainWindow()
    mainWindow.show()

    # downloadDirectory = QFileDialog.getExistingDirectory(None, u'Укажи директорию для закачки файлов')
    # platform = Linux(downloadDirectory)
    # boostBuilder = BoostBuilder(Downloader(u'Скачай последнюю версию библиотеки Boost', \
    #                                        'http://sourceforge.net/projects/boost/files/boost/', platform))
    # boostBuilder.build()

    sys.exit(app.exec_())

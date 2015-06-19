#!/usr/bin/env python
# encoding: utf-8

import sys, os
import subprocess
from PySide.QtGui import (QApplication, QFileDialog, QWidget)

from prebuild import *



# import subprocess, os, sys
# from PySide.QtGui import (QApplication, QTextEdit, QPushButton)
# from PySide.QtCore import (QProcess)


# class Step(object):
#     def __init__(self, program, args):
#         self.output = None
#         self.program = program
#         self.args = args

#         self.proc = QProcess()
#         self.proc.readyReadStandardOutput.connect(self.onReadStdOut)
#         self.proc.readyReadStandardError.connect(self.onReadStdOut)
#         self.proc.start(program, args)

#     def run(self):
        

#     def onReadStdOut(self):
#         self.textEdit.append(str(self.proc.readAllStandardOutput()))
#         self.textEdit.append(str(self.proc.readAllStandardError()))

#     def setOutput(self, output):
#         self.output = output


# class BuildProc(object):
#     def __init__(self, steps):
#         self.__steps = steps

#     def run(self):



# class MyProcess(object):
#     def __init__(self, textEdit, program, args):

#         self.textEdit = textEdit

#         self.proc = QProcess()
#         self.proc.readyReadStandardOutput.connect(self.onReadStdOut)
#         self.proc.readyReadStandardError.connect(self.onReadStdOut)
#         self.proc.start(program, args)

#     def onReadStdOut(self):
#         self.textEdit.append(str(self.proc.readAllStandardOutput()))
#         self.textEdit.append(str(self.proc.readAllStandardError()))


# if __name__ == '__main__':
#     app = QApplication(sys.argv)

#     te = QTextEdit()
#     te.resize(600, 300)
#     te.show()

#     proc = MyProcess(te, 
#         'wget', ['http://download.savannah.gnu.org/releases/freetype/freetype-2.6.tar.gz', '-P', 'Download'])

#     sys.exit(app.exec_())

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

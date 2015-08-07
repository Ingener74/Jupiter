#!/usr/bin/env python
# encoding: utf-8

import sys

from PySide.QtGui import (QApplication, QWidget, QTextEdit)
from PySide.QtCore import (QProcess, Qt)

from prebuild import (Ui_Main)


# noinspection PyPep8Naming,PyUnresolvedReferences
class Step(object):
    def __init__(self, program, args):
        self.textEdit = None
        self.output = None
        self.program = program
        self.args = args

        self.proc = QProcess()
        self.proc.readyReadStandardOutput.connect(self.onReadStdOut)
        self.proc.readyReadStandardError.connect(self.onReadStdOut)
        self.proc.start(program, args)

    def run(self):
        pass

    def onReadStdOut(self):
        self.textEdit.append(str(self.proc.readAllStandardOutput()))
        self.textEdit.append(str(self.proc.readAllStandardError()))

    def setOutput(self, output):
        self.output = output


class BuildProc(object):
    def __init__(self, steps):
        self.__steps = steps

    def run(self):
        pass


# noinspection PyUnresolvedReferences,PyPep8Naming,PyMethodMayBeStatic
class MyProcess(object):
    def __init__(self, textEdit, program, args):

        self.textEdit = textEdit

        # env = QProcess.systemEnvironment()
        #
        # # env.insert('PATH', env.value('Path') + ';C:\\cygwin64\\bin')
        #
        # self.proc = QProcess()
        #
        # # print env
        # for index, value in enumerate(env):
        #     if value.startswith(u'PATH'):
        #         env[index] = value + u';C:\\cygwin64\\bin'
        # print env
        #
        # self.proc.setEnvironment(env)
        #
        # self.proc.error.connect(self.onError)
        self.proc.readyReadStandardOutput.connect(self.onReadStdOut)
        self.proc.readyReadStandardError.connect(self.onReadStdOut)
        print self.proc.start(program, args)

    def onReadStdOut(self):
        self.textEdit.append(str(self.proc.readAllStandardOutput()))

    def onReadStdErr(self):
        # self.textEdit.append(str(self.proc.readAllStandardError()))
        print 'error: ', self.proc.readAllStandardError()

    def onError(self, procError):
        print procError


# if __name__ == '__main__':
#     app = QApplication(sys.argv)

#     te = QTextEdit()
#     te.resize(600, 300)
#     te.show()

#     proc = MyProcess(te, 
#         'wget', ['http://download.savannah.gnu.org/releases/freetype/freetype-2.6.tar.gz', '-P', 'Download'])

#     sys.exit(app.exec_())

# class BoostBuilder(Builder):
#     def __init__(self, downloader):
#         super(BoostBuilder, self).__init__(downloader)
#
#     def build(self):
#         self.downloader.show()
#
#         print 'after download'


class MainWindow(QWidget, Ui_Main):
    MIN_SIZE = 600

    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)

    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            raise SystemExit


# noinspection PyPep8Naming
if __name__ == '__main__':
    # noinspection PyCallByClass,PyTypeChecker
    QApplication.setStyle(u'plastique')
    app = QApplication(sys.argv)

    mainWindow = MainWindow()
    mainWindow.show()

    # downloadDirectory = QFileDialog.getExistingDirectory(None, u'Укажи директорию для закачки файлов')
    # platform = Linux(downloadDirectory)
    # boostBuilder = BoostBuilder(Downloader(u'Скачай последнюю версию библиотеки Boost', \
    #                                        'http://sourceforge.net/projects/boost/files/boost/', platform))
    # boostBuilder.build()

    bash = QProcess()
    print bash.start('bash')

    sys.exit(app.exec_())

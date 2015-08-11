# encoding: utf8
from PySide.QtCore import QThread


class BuildThread(QThread):
    def __init__(self):
        QThread.__init__(self)

    def run(self, *args, **kwargs):
        print 'BuildThread'

        packages = []

        for p in packages:
            print 'build package'

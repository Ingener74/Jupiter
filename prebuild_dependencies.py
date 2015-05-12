#!/usr/bin/env python
# encoding: utf-8

import sys
import subprocess
from PySide.QtGui import QApplication, QFileDialog

from prebuild.Linux import Linux
from prebuild.Downloader import Downloader
from prebuild.Builder import Builder


class BoostBuilder(Builder):
    def __init__(self, downloader):
        super(BoostBuilder, self).__init__(downloader)
    
    def build(self):
        self.downloader.show()
        
        print 'after download'


def main():
    app = QApplication(sys.argv)
    
    downloadDirectory = QFileDialog.getExistingDirectory(None, u'Укажи директорию для закачки файлов')
    platform = Linux(downloadDirectory)
    
    boostBuilder = BoostBuilder(Downloader(u'Скачай последнюю версию библиотеки Boost', \
                                           'http://sourceforge.net/projects/boost/files/boost/', platform))
    boostBuilder.build()
    
    return app.exec_()


if __name__ == '__main__':
    main()

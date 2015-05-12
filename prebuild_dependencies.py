#!/usr/bin/env python
# encoding: utf-8

import sys
import subprocess
from PySide.QtGui import QApplication, QFileDialog
from PySide.QtWebKit import QWebView

from prebuild.Linux import Linux

class Builder(object):
    def __init__(self, downloader):
        self.downloader = downloader
    
    def build(self):
        raise SystemExit(u"not implemented")

class BoostBuilder(Builder):
    def __init__(self, downloader):
        super(BoostBuilder, self).__init__(downloader)
    
    def build(self):
        self.downloader.show()
        
        print 'after download'

class Downloader(QWebView):
    def __init__(self, title, link, platform):
        super(Downloader, self).__init__()
        
        self.platform = platform

        self.load(link)

        self.page().setForwardUnsupportedContent(True)
        self.page().unsupportedContent.connect(self.content)
        
        self.setWindowTitle(title)

    def content(self, reply):
        self.file = reply.request().url().toString()
        self.afterDownload()
        
    def afterDownload(self):
        self.close()
        self.platform.downloadFile(self.file)


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

#!/usr/bin/env python
# encoding: utf-8

import sys
from PySide.QtGui import QApplication
from PySide.QtWebKit import QWebView

class Downloader(QWebView):
    def __init__(self, title, link):
        super(Downloader, self).__init__()

        self.load(link)

        self.page().setForwardUnsupportedContent(True)
        self.page().unsupportedContent.connect(self.content)
        
        self.setWindowTitle(title)

    def content(self, reply):
        self.file = reply.request().url().toString()
        self.afterDownload()
        
    def afterDownload(self):
        raise SystemExit(u'Отнаследуйся придурок это базовый класс: ' + self.file)

class BoostDownloader(Downloader):
    def __init__(self, title, link):
        super(BoostDownloader, self).__init__(title, link)
    
    def afterDownload(self):
        print self.file


class Platform(object):
    def __init__(self):
        pass
    
    def downloadFile(self, file):
        raise SystemExit(u'Неправильная платформа')

class Win(Platform):
    def __init__(self):
        super(Win, self).__init__()
        pass

def main():
    app = QApplication(sys.argv)
    
    platform = Win()
    
    boost_downloader = BoostDownloader(u'Скачай последнюю версию библиотеки Boost', 'http://sourceforge.net/projects/boost/files/boost/')
    boost_downloader.show()
    
    return app.exec_()

if __name__ == '__main__':
    main()
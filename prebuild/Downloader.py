#!/usr/bin/env python
# encoding: utf-8

from PySide.QtWebKit import QWebView

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

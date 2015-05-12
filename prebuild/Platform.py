#!/usr/bin/env python
# encoding: utf-8

class Platform(object):
    def __init__(self, downloadDirectory):
        pass
        
        self.downloadDirectory = downloadDirectory
    
    def downloadFile(self, File):
        raise SystemExit(u'Неправильная платформа')

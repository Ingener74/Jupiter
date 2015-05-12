#!/usr/bin/env python
# encoding: utf-8

from Platform import Platform

class Linux(Platform):
    def __init__(self, downloadDirectory):
        super(Linux, self).__init__(downloadDirectory)
    
    def downloadFile(self, File):
        wgetProcess = subprocess.Popen(['wget', File, '-P', self.downloadDirectory])
        wgetProcess.wait()

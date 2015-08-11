# encoding: utf-8

class Builder(object):
    def __init__(self, downloader):
        self.downloader = downloader
    
    def build(self):
        raise SystemExit(u"not implemented")

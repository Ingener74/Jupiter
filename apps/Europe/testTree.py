#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
from modules import *
from PySide.QtGui import *
from PySide.QtCore import *

class TreeView(QTreeView):
    def __init__(self, parent=None):
        QTreeView.__init__(self, parent)
    
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    dir = QFileDialog.getExistingDirectory(caption=u'Директория с ресурсами', options=QFileDialog.ShowDirsOnly)
    resModel = ResourceModel(dir)
    
    treeView = TreeView()
    treeView.setModel(resModel)
    treeView.show()
    
    sys.exit(app.exec_())



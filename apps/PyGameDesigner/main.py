#!/usr/bin/env python
# -*- coding: utf-8 -*-

from PySide.QtGui import QWidget, QApplication
from main_editor_window import Ui_EditorMain

class MainEditorWindow(QWidget, Ui_EditorMain):
    def __init__(self, parent=None):
        super(MainEditorWindow,self).__init__(parent)
        self.setupUi(self)

def main():
    import sys
    app = QApplication(sys.argv)
    
    mainWindow = MainEditorWindow()
    mainWindow.show()
    
    sys.exit(app.exec_())

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print str(e)
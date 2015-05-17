#!/usr/bin/env python
# -*- coding: utf-8 -*-

from PySide.QtGui import QWidget, QApplication, QMainWindow, QVBoxLayout, QMenu, QPushButton, QTreeView, QHBoxLayout
from PySide.QtOpenGL import QGLWidget
from PySide.QtCore import Qt

from OpenGL.GL import *
from OpenGL.GLU import *

from res import *


class GlWidget(QGLWidget):
    def __init__(self, parent=None):
        super(GlWidget, self).__init__(parent, None)
        
    def initializeGL(self):
        print 'Vendor   ', str(glGetString(GL_VENDOR))
        print 'Renderer ', str(glGetString(GL_RENDERER))
        print 'OpenGL   ', str(glGetString(GL_VERSION))
        print 'GLSL     ', str(glGetString(GL_SHADING_LANGUAGE_VERSION))
#         self.resize(800, 480) # try this
        
    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glClearColor(0.1, 0.3, 0.1, 1.0)
        
    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)
        
        
class GameDesignerWindow(QWidget, Ui_GameDesigner):
    def __init__(self, parent=None):
        super(GameDesignerWindow,self).__init__(parent)
        self.setupUi(self)
        
        self.glLayout.addWidget(GlWidget())
        
        self.addNodeMenu = QMenu()
        self.addNodeMenu.addAction(u'Добавить спрайт', self.addSpriteAction)
        self.addNodeButton.setMenu(self.addNodeMenu)
        
        
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()
        
    def addSpriteAction(self):
        print 'add sprite action'
        
    def addSprite(self):
        print 'add sprite'
        
        
def main():
    import sys
    app = QApplication(sys.argv)
    
    mainWindow = GameDesignerWindow()
    mainWindow.show()
    
    sys.exit(app.exec_())

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print 'Exception {}'.format(str(e))







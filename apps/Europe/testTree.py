#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
from modules import *
from PySide.QtGui import *
from PySide.QtCore import *
from PySide.QtOpenGL import *
from OpenGL.GL import *
from OpenGL.GLU import *

class GlWidget(QGLWidget):
    
    WIDTH = 100
    HEIGHT = WIDTH * 3 / 5
    
    def __init__(self, parent=None):
        QGLWidget.__init__(self, parent, None)
        self.resize(self.WIDTH, self.HEIGHT)
        
    def initializeGL(self):
        print 'Vendor   ', str(glGetString(GL_VENDOR))
        print 'Renderer ', str(glGetString(GL_RENDERER))
        print 'OpenGL   ', str(glGetString(GL_VERSION))
        print 'GLSL     ', str(glGetString(GL_SHADING_LANGUAGE_VERSION))
        
    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glClearColor(0.1, 0.3, 0.1, 1.0)
        
    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)

class TestWidget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        
#         d = QFileDialog.getExistingDirectory(caption=u'Директория с ресурсами', options=QFileDialog.ShowDirsOnly).encode('ascii', 'ignore')
        
        glWidget = GlWidget()
        treeView = QTreeView()
        
        resModel = ResourceModel('/home/pavel/workspace/Jupiter/samples/Box')
#         resModel = ResourceModel(d)
        treeView.setModel(resModel)
        
        vbox = QVBoxLayout()
        vbox.addWidget(glWidget)
        vbox.addWidget(treeView)
        
        self.setLayout(vbox)
        
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    test = TestWidget()
    test.show()
    
    sys.exit(app.exec_())



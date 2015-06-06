#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import math

from PySide.QtCore import *
from PySide.QtGui import QApplication, QKeyEvent, QKeySequence, QMessageBox, QWidget, QIcon, QPixmap
from PySide.QtOpenGL import QGLWidget, QGLFormat, QGLContext

from modules import *
from res import *

PLAYER_TITLE = u"Игровой плеер на движке Юпитер"

try:
    from OpenGL.GL   import *
    from OpenGL.GLU  import *
    from OpenGL.GLUT import *
except ImportError as e:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, \
                         PLAYER_TITLE, \
                         u'Установи PyOpenGL', \
                         QMessageBox.Ok | QMessageBox.Default,\
                         QMessageBox.NoButton)
    sys.exit(1)

class OpenGLWidget(QGLWidget):
    def __init__(self, parent=None):
        QGLWidget.__init__(self, parent, None)
        self.setWindowIcon(QIcon(QPixmap(':/main.png')))
        
        self.fallingBox = None

    def initializeGL(self):
        self.setWindowTitle(PLAYER_TITLE)
        self.resize(FallingBox.WIDTH, FallingBox.HEIGTH)
        
        print 'Vendor   ', str(glGetString(GL_VENDOR))
        print 'Renderer ', str(glGetString(GL_RENDERER))
        print 'OpenGL   ', str(glGetString(GL_VERSION))
        print 'GLSL     ', str(glGetString(GL_SHADING_LANGUAGE_VERSION))
        
        glEnable(GL_TEXTURE_2D)
        glEnable(GL_DEPTH_TEST)
        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        
        try:
            j.startJupiter()
            self.fallingBox = FallingBox(self, self.width(), self.height())
            
            self.startTimer(1000.0 / self.fallingBox.FPS)
            
        except RuntimeError, e:
            raise SystemExit(u'Ошибка старта ' + str(e))

    def paintGL(self):
        glClearColor(0.1, 0.3, 0.1, 1.0)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        
        try:
            if self.fallingBox != None and self.fallingBox.isReady():
                self.fallingBox.game.draw()
                
        except RuntimeError, e:
            raise SystemExit(str(e))
    
    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)
    
    def timerEvent(self, event):
        self.update()
    
    def keyPressEvent(self, event):
        if event.key() == Qt.Key_F5:
            self.fallingBox = FallingBox(self, self.width(), self.height())
        if event.key() == Qt.Key_Escape:
            raise SystemExit
        self.fallingBox.game.keyboard(event.nativeScanCode())
    
    def closeEvent(self, e):
        j.endJupiter()


class Select(QWidget, Ui_SelectImpl):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        self.PySideButton.clicked.connect(self.pySide)
        self.FreeGlutButton.clicked.connect(self.glut)
        
    def pySide(self):
        window = OpenGLWidget()
        window.show()
        self.close()
    
    def glut(self):
        pass


def setStyle():
    if sys.platform == 'win32':
        QApplication.setStyle(u"windows")
    elif sys.platform == 'linux2':
        QApplication.setStyle(u"plastique")
    else:
        print u'Неизвестная система'

def main():
    setStyle()
    app = QApplication(sys.argv)
    
    select = Select()
    select.show()

    sys.exit(app.exec_())

if __name__ == '__main__':
    try:
        main()
    except RuntimeError, e:
        print str(e)


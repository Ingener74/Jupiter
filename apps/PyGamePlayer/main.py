#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import math

from PySide.QtCore import *
from PySide.QtGui import QApplication, QKeyEvent, QKeySequence, QMessageBox
from PySide.QtOpenGL import QGLWidget, QGLFormat

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

try:
    # Установи в PYTHONPATH путь до библеотеки _Jupiter.{so, pyd, dll} и PyJupiter.py
    import PyJupiter as j
except ImportError as e:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, \
                         PLAYER_TITLE, \
                         u'Установи в PYTHONPATH путь до библиотеки _Jupiter.{so, pyd, dll} и PyJupiter.py', \
                         QMessageBox.Ok | QMessageBox.Default,\
                         QMessageBox.NoButton)
    sys.exit(1)


class BgMove(j.MoveListener):
    def __init__(self, window):
        super(BgMove, self).__init__()
        
        self.window = window
    
    def move(self, x, y, z):
        print '(', x, '; ', y, '; ',z, ')'
        if x > 2:
            self.window.close()

class FallingBox(object):
    def __init__(self, window, width, height):
        
        j.File.setBase('../../samples/Box')
        
        self.shader = j.FileShader(j.File('Resources/sprite.vs'), j.File('Resources/sprite.fs'))
        
        self.camera = j.Camera(45.0,            \
                               width, height,   \
                               1.0, 1000.0,     \
                               0.0, 0.0, 100.0, \
                               0.0, 0.0, 0.0,   \
                               0.0, 1.0, 0.0)
        
        # self.print_visitor = j.PrintVisitor()
        self.render = j.RenderVisitor(self.camera)
        
        self.rn = j.Node()
        
        bgImage = j.PngImage('Resources/bg.png')
        self.bgTexture = j.ImageTexture(bgImage)
        self.bgShape = j.ImageShape(bgImage)
        self.bgMove = BgMove(window)
        self.bg = j.Sprite()
        self.bg.setProgram(self.shader).\
            setTexture(self.bgTexture).\
            setShape(self.bgShape).\
            setMoveListener(self.bgMove).\
            setVisible(True).\
            setParent(self.rn).\
            setScale(0.08, 0.08)
        
        self.rn.addNode(self.bg)
        
        self.game = j.Game()
        self.game.setRootNode(self.rn).\
            addVisitor(self.render).\
            setWidth(width).\
            setHeight(height)
            # addVisitor(self.print_visitor).\


class OpenGLWidget(QGLWidget):
    def __init__(self, parent=None):
        super(OpenGLWidget, self).__init__(parent, None)
        self.falling_box = None

    def initializeGL(self):
        self.setWindowTitle(PLAYER_TITLE)
        
        glEnable(GL_TEXTURE_2D)
        glEnable(GL_DEPTH_TEST)
        
        try:
            j.initJupiter()
            self.falling_box = FallingBox(self, self.width(), self.height())
            
            self.startTimer(1000.0 / 30.0)
            
        except RuntimeError, e:
            raise SystemExit(str(e))

    def paintGL(self):
        self.makeCurrent()

        glClearColor(0.1, 0.3, 0.1, 1.0)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        
        if self.falling_box == None:
            pass
        else:
            self.falling_box.bg.translateX(0.5)
            self.falling_box.game.draw()
        
        self.swapBuffers()
    
    def timerEvent(self, event):
        self.update()
    
    def keyPressEvent(self, event):
        if event.nativeScanCode() == 9:
            raise SystemExit


def main():
    app = QApplication(sys.argv)
    
    # format = QGLFormat()
    # format.setVersion(3, 3)
    # format.setProfile(QGLFormat.CoreProfile)
    # window = OpenGLWidget(format)

    window = OpenGLWidget()
    window.show()
     
    sys.exit(app.exec_())


if __name__ == '__main__':
    try:
        main()
    except RuntimeError, e:
        print str(e)


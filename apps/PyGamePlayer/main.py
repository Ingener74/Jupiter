#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import math

from PySide.QtCore import *
from PySide.QtGui import QApplication, QKeyEvent, QKeySequence, QMessageBox
from PySide.QtOpenGL import QGLWidget, QGLFormat

try:
    from OpenGL.GL   import *
    from OpenGL.GLU  import *
    from OpenGL.GLUT import *
except ImportError as e:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, \
                         u"Игровой плеер на движке Юпитер", \
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
                         u"Игровой плеер на движке Юпитер", \
                         u'Установи в PYTHONPATH путь до библеотеки _Jupiter.{so, pyd, dll} и PyJupiter.py', \
                         QMessageBox.Ok | QMessageBox.Default,\
                         QMessageBox.NoButton)
    sys.exit(1)


class FallingBox(object):
    
    WIDTH = 800
    HEIGHT = 480
    
    def __init__(self, width, height):
        j.File.setBase('../../samples/Box')
        
        vs = j.File('Resources/sprite.vs')
        fs = j.File('Resources/sprite.fs')
        self.shader = j.FileShader(vs, fs)
    
        self.camera = j.Camera(45.0,            \
                               width, height,   \
                               1.0, 1000.0,     \
                               0.0, 0.0, 100.0, \
                               0.0, 0.0, 0.0,   \
                               0.0, 1.0, 0.0)
        
#         self.print_visitor = j.PrintVisitor()
        self.render = j.RenderVisitor(self.camera)
        
        self.rn = j.Node()
        
        self.bg_image = j.PngImage('Resources/bg.png')
        self.bg_texture = j.ImageTexture(self.bg_image)
        self.bg_shape = j.ImageShape(self.bg_image)
        self.bg = j.Sprite()
        self.bg.setProgram(self.shader).\
            setTexture(self.bg_texture).\
            setShape(self.bg_shape).\
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

    def getGame(self):
        return self.game


class MyOpenGLWidget(QGLWidget):
    def __init__(self, parent=None):
        super(MyOpenGLWidget, self).__init__(parent)
        
        self.falling_box = None

    def initializeGL(self):
        glEnable(GL_TEXTURE_2D)
        glEnable(GL_DEPTH_TEST)
        
        try:
            j.initJupiter()
            self.falling_box = FallingBox(self.width(), self.height())
            
            self.startTimer(1000.0 / 30.0)
            
        except j.JupiterError as e:
            print e.what()

    def paintGL(self):
        self.makeCurrent()

        glClearColor(0.1, 0.3, 0.1, 1.0)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        
        if self.falling_box == None:
            pass
        else:
            self.falling_box.getGame().draw()
        
        self.swapBuffers()
    
    def timerEvent(self, event):
        self.update()
    
    def keyPressEvent(self, event):
        if event.nativeScanCode() == 9:
            raise SystemExit


def main():
    app = QApplication(sys.argv)

#     glformat = QGLFormat()
#     glformat.setVersion(3, 3)
#     glformat.setProfile(QGLFormat.CoreProfile)

    window = MyOpenGLWidget()
    window.show()
     
    sys.exit(app.exec_())


if __name__ == '__main__':
    try:
        main()
    except j.JupiterError as e:
        print e.what()
    except Exception as e:
        print str(e)








#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import math

from OpenGL.GL   import *
from OpenGL.GLU  import *
from OpenGL.GLUT import *
from PySide.QtGui import QApplication
from PySide.QtOpenGL import QGLWidget

# Установи в PYTHONPATH путь до библеотеки _Jupiter.{so, pyd, dll} и PyJupiter.py
import PyJupiter as j
from PySide import QtOpenGL

# class BackGround(j.Controller):
#     def __init__(self):
#         j.Controller.__init__(self)
#         
#     def update(self, elapsedTime):
#         pass


class FallingBox(object):
    
    WIDTH = 800
    HEIGHT = 480
    
    def __init__(self):
        j.File.setBase('../../samples/Box')
        
        vs = j.File('Resources/sprite.vs')
        fs = j.File('Resources/sprite.fs')
        self.shader = j.FileShader(vs, fs)
        
        print 'test'
        
        self.render = j.RenderVisitor()
        
        self.bg_image = j.PngImage('Resources/bg.png')
        self.bg_texture = j.ImageTexture(self.bg_image)
        self.bg_shape = j.ImageShape(self.bg_image)
        
        self.bg = j.Node()
        
        self.rn = j.Node()
        self.rn.addNode(self.bg)
        
        self.game = j.Game()
        self.game.setRootNode(self.rn).setVisitors([self.render]).setWidth(WIDTH).setHeight(HEIGTH)
        
    def getGame(self):
        return self.game


class MyOpenGLWidget(QGLWidget):
    def __init__(self, parent=None):
        super(MyOpenGLWidget, self).__init__(parent)
        
        self.makeCurrent()

        try:
            j.initJupiter()
            self.falling_box = FallingBox()
            
        except j.JupiterError as e:
            print e.what()
    
    def paintGL(self, *args, **kwargs):
        
        glClearColor(0.1, 0.3, 0.1, 1.0)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        
        self.falling_box.getGame().draw()


def main():
    app = QApplication(sys.argv)

    glformat = QtOpenGL.QGLFormat()
    glformat.setVersion(3, 3)
    glformat.setProfile(QtOpenGL.QGLFormat.CoreProfile)

    window = MyOpenGLWidget(glformat)
    window.show()
     
    app.exec_()


if __name__ == '__main__':
    try:
        main()
    except j.JupiterError as e:
        print e.what()
    except Exception as e:
        print str(e)








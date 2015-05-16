#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import math

from PySide.QtCore import *
from PySide.QtGui import QApplication, QKeyEvent, QKeySequence, QMessageBox, QWidget
from PySide.QtOpenGL import QGLWidget, QGLFormat, QGLContext

from move import Ui_MoveDialog

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


class BoxMove(j.MoveListener):
    def __init__(self, window):
        super(BoxMove, self).__init__()
        self.window = window
    
    def move(self, x, y, z):
        if y < -30:
            self.window.close()


class BoxScale(j.ScaleListener):
    def scale(self, x, y, z):
        pass


class FallingBox(object):
    
    WIDTH  = 800
    HEIGTH = WIDTH * 3.0 / 5.0
    
    FPS    = 60.0
    
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
        self.physics = j.Box2dVisitor(1.0 / self.FPS)
        self.render = j.RenderVisitor(self.camera)
        
        self.rn = j.Node()
        
        bgImage = j.PngImage('Resources/bg.png')
        self.bgTexture = j.ImageTexture(bgImage)
        self.bgShape = j.ImageShape(bgImage)
        self.bg = j.Sprite()
        self.bg.\
            setProgram(self.shader).\
            setTexture(self.bgTexture).\
            setShape(self.bgShape).\
            setVisible(True).\
            setScale(0.11)
        
        self.boxMove = BoxMove(window)
        self.boxScale = BoxScale()
        boxImage = j.PngImage('Resources/box.png')
        self.boxTex = j.ImageTexture(boxImage)
        self.boxShape = j.ImageShape(boxImage)
        self.box = j.Sprite()
        self.box.\
            setProgram(self.shader).\
            setTexture(self.boxTex).\
            setShape(self.boxShape).\
            setMoveListener(self.boxMove).\
            setScaleListener(self.boxScale).\
            setVisible(True).\
            translate(0.0, 40.0, 10.0).\
            setScale(0.02)
        
        groundImage = j.PngImage('Resources/ground.png')
        self.groundTex = j.ImageTexture(groundImage)
        self.groundShape = j.ImageShape(groundImage)
        
        self.ground1 = j.Sprite()
        self.ground1.\
            setProgram(self.shader).\
            setTexture(self.groundTex).\
            setShape(self.groundShape).\
            setVisible(True).\
            translate(0.0, -40.0, 10.0).\
            scale(0.1)
        
        self.ground2 = j.Sprite()
        self.ground2.\
            setProgram(self.shader).\
            setTexture(self.groundTex).\
            setShape(self.groundShape).\
            setVisible(True).\
            translate(30.0, -40.0, 10.0).\
            scale(0.1)
        
        self.ground3 = j.Sprite()
        self.ground3.\
            setProgram(self.shader).\
            setTexture(self.groundTex).\
            setShape(self.groundShape).\
            setVisible(True).\
            translate(-30.0, -40.0, 10.0).\
            scale(0.1)
        
        self.rn.\
            addNode(self.bg).\
            addNode(self.box).\
            addNode(self.ground1).\
            addNode(self.ground2).\
            addNode(self.ground3)
        
        self.game = j.Game()
        self.game.setRootNode(self.rn).\
            addVisitor(self.render).\
            setWidth(width).\
            setHeight(height)
            # addVisitor(self.print_visitor).\


class MoveWidget(QWidget, Ui_MoveDialog):
    def __init__(self, game, parent=None):
        super(MoveWidget, self).__init__(parent)
        self.setupUi(self)
        self.game = game
        
        self.pushButtonUp.clicked.connect(self.upClick)
        self.pushButtonDown.clicked.connect(self.downClick)
        self.pushButtonLeft.clicked.connect(self.leftClick)
        self.pushButtonRight.clicked.connect(self.rightClick)
        
    def upClick(self):
        self.game.box.translateY(10 ** self.comboBoxValue.currentIndex())
    
    def downClick(self):
        self.game.box.translateY(-10 ** self.comboBoxValue.currentIndex())
    
    def leftClick(self):
        self.game.box.translateX(-10 ** self.comboBoxValue.currentIndex())
    
    def rightClick(self):
        self.game.box.translateX(10 ** self.comboBoxValue.currentIndex())


class OpenGLWidget(QGLWidget):
    def __init__(self, parent=None):
        super(OpenGLWidget, self).__init__(parent, None)
        self.falling_box = None

    def initializeGL(self):
        self.setWindowTitle(PLAYER_TITLE)
        self.resize(FallingBox.WIDTH, FallingBox.HEIGTH)
        
        print 'Vendor   ', str(glGetString(GL_VENDOR))
        print 'Renderer ', str(glGetString(GL_RENDERER))
        print 'OpenGL   ', str(glGetString(GL_VERSION))
        print 'GLSL     ', str(glGetString(GL_SHADING_LANGUAGE_VERSION))
        
        glEnable(GL_TEXTURE_2D)
        glEnable(GL_DEPTH_TEST)
        
        try:
            j.initJupiter()
            self.falling_box = FallingBox(self, self.width(), self.height())
            
            self.moveWindow = MoveWidget(self.falling_box)
            self.moveWindow.show()
            
            self.startTimer(1000.0 / 30.0)
            
        except RuntimeError, e:
            raise SystemExit(str(e))

    def paintGL(self):
        glClearColor(0.1, 0.3, 0.1, 1.0)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        
        if self.falling_box == None:
            pass
        else:
#             self.falling_box.bg.\
#                 translateX(1).\
#                 rotateZ(0.005)
#             self.falling_box.box.\
#                 translateY(-20)
#                 rotateZ(0.03).\
            
            self.falling_box.game.draw()
    
    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)
    
    def timerEvent(self, event):
        self.update()
    
    def keyPressEvent(self, event):
        if event.nativeScanCode() == 9:
            raise SystemExit
    
    def closeEvent(self, e):
        self.moveWindow.close()


def main():
    app = QApplication(sys.argv)
    
#     format = QGLFormat()
#     format.setVersion(3, 3)
#     format.setProfile(QGLFormat.CoreProfile)
#     format.setSampleBuffers(True)
#     window = OpenGLWidget(format)

    window = OpenGLWidget()
    
    window.show()
     
    sys.exit(app.exec_())


if __name__ == '__main__':
    try:
        main()
    except RuntimeError, e:
        print str(e)


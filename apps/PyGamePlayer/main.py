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

class Box(j.MoveListener, j.KeyboardListener, j.ScaleListener):
    def __init__(self, window):
        j.MoveListener.__init__(self)
        j.ScaleListener.__init__(self)
        j.KeyboardListener.__init__(self)
        
        self.window = window
    
    def move(self, x, y, z):
        print 'move ',[x, y, z]
    
    def scale(self, x, y, z):
        print 'scale ', [x, y, z]
    
    def key(self, key):
        print 'key ', key
        if key == 113:
            self.getNode().translateX(-5)
        if key == 114:
            self.getNode().translateX(5)
        

class BgRotate(j.RotationListener):
    def rotate(self, x, y, z, angle):
        print [x, y, z, angle]

class FallingBox(object):
    
    WIDTH  = 200 #800
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
        
        self.printVisitor  = j.PrintVisitor()
        self.physics       = j.Box2dVisitor(1.0 / self.FPS)
        self.render        = j.RenderVisitor(self.camera)
        
        self.rn = j.Node()
        
        self.bgRotate = BgRotate()
        bgImage = j.PngImage('Resources/bg.png')
        self.bgTexture = j.ImageTexture(bgImage)
        self.bgShape = j.ImageShape(bgImage)
        self.bg = j.Sprite()
        self.bg.\
            setProgram(self.shader).\
            setTexture(self.bgTexture).\
            setShape(self.bgShape).\
            setRotationListener(self.bgRotate).\
            setScale(0.11)#.\
            #setRotationZ(1.5)
        
            #setScaleListener(self.boxTest).\
        self.boxTest = Box(window)
        boxImage = j.PngImage('Resources/box.png')
        self.boxTex = j.ImageTexture(boxImage)
        self.boxShape = j.ImageShape(boxImage)
        self.box = j.Sprite()
        self.box.\
            setProgram(self.shader).\
            setTexture(self.boxTex).\
            setShape(self.boxShape).\
            setMoveListener(self.boxTest).\
            translate(0.0, 40.0, 10.0).\
            setScale(0.02)
        
        groundImage = j.PngImage('Resources/ground.png')
        self.groundTex = j.ImageTexture(groundImage)
        self.groundShape = j.ImageShape(groundImage)
        
        self.grounds = [j.Sprite() for i in range(0, 4)]
        
        self.grounds[0].\
            setProgram(self.shader).\
            setTexture(self.groundTex).\
            setShape(self.groundShape).\
            translate(0.0, -40.0, 10.0).\
            scale(0.1)
        
        self.grounds[1].\
            clone(self.grounds[0]).\
            translate(34.0, -4.0, 0.0)
        
        self.grounds[2].\
            clone(self.grounds[0]).\
            translate(-34.0, 4.0, 0.0)

        self.grounds[3].\
            clone(self.grounds[2]).\
            translate(-34.0, 4.0, 0.0)
        
        self.rn.\
            addNode(self.bg).\
            addNode(self.box).\
            addNode(self.grounds[0]).\
            addNode(self.grounds[1]).\
            addNode(self.grounds[2]).\
            addNode(self.grounds[3])
        
            #addVisitor(self.printVisitor).\
        self.game = j.Game()
        self.game.setRootNode(self.rn).\
            addVisitor(self.render).\
            addKeyboardListener(self.boxTest).\
            setWidth(width).\
            setHeight(height)


class MoveWidget(QWidget, Ui_MoveDialog):
    def __init__(self, game, parent=None):
        QWidget.__init__(self, parent)
        
        self.setupUi(self)
        self.game = game
        
        self.pushButtonUp.clicked.connect(self.upClick)
        self.pushButtonDown.clicked.connect(self.downClick)
        self.pushButtonLeft.clicked.connect(self.leftClick)
        self.pushButtonRight.clicked.connect(self.rightClick)
        
    def upClick(self):
        self.game.box.translateY(10 ** self.comboBoxValue.currentIndex())
        self.printPos()
    
    def downClick(self):
        self.game.box.translateY(-10 ** self.comboBoxValue.currentIndex())
        self.printPos()
    
    def leftClick(self):
        self.game.box.translateX(-10 ** self.comboBoxValue.currentIndex())
        self.printPos()
    
    def rightClick(self):
        self.game.box.translateX(10 ** self.comboBoxValue.currentIndex())
        self.printPos()
    
    def printPos(self):
        print 'box position ',[self.game.box.getPositionX(), self.game.box.getPositionY(), self.game.box.getPositionZ()]


class OpenGLWidget(QGLWidget):
    def __init__(self, parent=None):
        QGLWidget.__init__(self, parent, None)
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
        
        if self.falling_box != None:
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
        if event.key() == Qt.Key_Escape:
            raise SystemExit
        self.falling_box.game.keyboard(event.nativeScanCode())
    
    def closeEvent(self, e):
        self.moveWindow.close()


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


#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import math

from PySide.QtCore import *
from PySide.QtGui import QApplication, QKeyEvent, QKeySequence, QMessageBox, QWidget, QIcon, QPixmap
from PySide.QtOpenGL import QGLWidget, QGLFormat, QGLContext

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

try:
    import JupiterPython as j
except ImportError as e:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, \
                         PLAYER_TITLE, \
                         u'Установи в PYTHONPATH путь до библиотеки _JupiterPython.{so, pyd, dll} и JupiterPython.py', \
                         QMessageBox.Ok | QMessageBox.Default,\
                         QMessageBox.NoButton)
    sys.exit(1)

class Box(j.MoveListener, j.ScaleListener, j.KeyboardListener):
    def __init__(self, window):
        j.MoveListener.__init__(self)
        j.ScaleListener.__init__(self)
        j.KeyboardListener.__init__(self)
        
        self.window = window
    
    def move(self, x, y, z):
#         print 'move ',[x, y, z]
        pass
    
    def scale(self, x, y, z):
#         print 'scale ', [x, y, z]
        pass
    
    def key(self, key):
#         print 'key ', key
        if key == 111 or key == 328:
            self.getNode().translateY(5)
        if key == 116 or key == 336:
            self.getNode().translateY(-5)
        if key == 113 or key == 331:
            self.getNode().translateX(-5)
        if key == 114 or key == 333:
            self.getNode().translateX(5)

class BoxCollision(j.CollisionListener):
    def __init__(self):
        j.CollisionListener.__init__(self)
        
    def collision(self, node):
        #print u'Я столкнулся с ', node.getName(), u' тег ', node.getTag()
        #self.getBox2dNode().applyForceToCenter(0., 3., True)
        pass

class BgRotate(j.RotationListener):
    def rotate(self, x, y, z, angle):
        print [x, y, z, angle]

DEG2RAD = 3.1415926 / 180.
RAD2DEG = 180. / 3.1415926

class FallingBox(object):
    
    WIDTH  = 800
    HEIGTH = WIDTH * 3.0 / 5.0
    
    FPS    = 60.0
    
    GROUND = 2
    
    def __init__(self, window, width, height):
        
        j.File.setBase('../../samples/Box')
        
        self.shader = j.FileShader(j.File('Resources/sprite.vs'), j.File('Resources/sprite.fs'))
        #self.box2dSh = j.FileShader(j.File('Resources/box2d.vs'), j.File('Resources/box2d.fs'))
        
        self.camera = j.Camera(45.0,            \
                               width, height,   \
                               1.0, 1000.0,     \
                               0.0, 0.0, 10.0, \
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
            translate(0., 0., -1.).\
            setScale(0.012)
            
            
            #setScaleListener(self.boxTest).\
        self.boxTest = Box(window)
        self.boxCol = BoxCollision()
        boxImage = j.PngImage('Resources/box.png')
        self.boxTex = j.ImageTexture(boxImage)
        self.boxShape = j.ImageShape(boxImage)
        
        boxDef = j.BodyDef()
        boxDef.type = j.dynamicBody;
        boxFixDef = j.FixtureDef()
        boxFixDef.density = 1.
        
        self.box1 = j.SpriteBox2d(self.physics, boxDef, boxFixDef)
        self.box1.setPhysicsShape(boxImage)
        self.box1.\
            setProgram(self.shader).\
            setTexture(self.boxTex).\
            setShape(self.boxShape).\
            setMoveListener(self.boxTest).\
            translate(0, 4, 1).\
            setScale(0.002)
        self.box1.setCollisionListener(self.boxCol)
        
        self.box2 = j.SpriteBox2d()
        self.box2.clone(self.box1).\
            setAngularVelocity(-30).\
            setScale(.0015, .0015, .0015).\
            setPosition(-.6, -2, 1)
        
        self.box3 = j.SpriteBox2d()
        self.box3.clone(self.box1).\
            setAngularVelocity(1).\
            setPosition(0, 3, 1).\
            setScale(.001, .001, .001)
        
        self.box4 = j.SpriteBox2d()
        self.box4.clone(self.box3).setPosition(-2, 2, 1)
        
        self.box5 = j.SpriteBox2d()
        self.box5.clone(self.box3).setPosition(-3, 3, 1)
        
        self.box6 = j.SpriteBox2d()
        self.box6.clone(self.box3).setScale(.002, .002, .002).setPosition(0, 3, 1)
        
        self.box7 = j.SpriteBox2d()
        self.box7.clone(self.box6).setPosition(4, 3, 1).setRotation(0, 0, 1, 30 * DEG2RAD)
        
        
        groundImage = j.PngImage('Resources/ground.png')
        self.groundTex = j.ImageTexture(groundImage)
        self.groundShape = j.ImageShape(groundImage)
        
        groundProto = j.SpriteBox2d(self.physics, j.BodyDef(), j.FixtureDef())
        groundProto.setProgram(self.shader).\
            setTexture(self.groundTex).\
            setShape(self.groundShape).\
            setName('flour').\
            setTag(self.GROUND)
        
        
        self.grounds = [j.SpriteBox2d() for i in range(0, 4)]
        for i in xrange(0, 4):
            self.grounds[i].clone(groundProto).\
                setPhysicsShape(groundImage).\
                scale(.01, .01, .01)
        
        self.grounds[0].translate(-2, -4, 1)
        self.grounds[1].translate( 2, -4, 1)
        self.grounds[2].translate(-5.5, -3.3, 1).setRotation(0, 0, 1, (360 - 30) * DEG2RAD)
        self.grounds[3].translate( 5.5, -3.3, 1).setRotation(0, 0, 1,  30 * DEG2RAD)
        
        self.rn.\
            addNode(self.bg).\
            addNode(self.box1).\
            addNode(self.box2).\
            addNode(self.box3).\
            addNode(self.box4).\
            addNode(self.box5).\
            addNode(self.box6).\
            addNode(self.box7).\
            addNode(self.grounds[0]).\
            addNode(self.grounds[1]).\
            addNode(self.grounds[2]).\
            addNode(self.grounds[3])
        
            #addVisitor(self.printVisitor).\
        self.game = j.Game()
        self.game.setRootNode(self.rn).\
            addVisitor(self.physics).\
            addVisitor(self.render).\
            addKeyboardListener(self.boxTest).\
            setWidth(width).\
            setHeight(height)


class OpenGLWidget(QGLWidget):
    def __init__(self, parent=None):
        QGLWidget.__init__(self, parent, None)
        self.setWindowIcon(QIcon(QPixmap('res/main.png')))
        
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
            if self.fallingBox != None:
                self.fallingBox.game.draw()
                
        except RuntimeError, e:
            raise SystemExit(str(e))
    
    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)
    
    def timerEvent(self, event):
        self.update()
    
    def keyPressEvent(self, event):
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
    
#     format = QGLFormat()
#     format.setVersion(3, 3)
#     format.setProfile(QGLFormat.CoreProfile)
#     format.setSampleBuffers(True)
#     window = OpenGLWidget(format)

    sys.exit(app.exec_())

if __name__ == '__main__':
    try:
        main()
    except RuntimeError, e:
        print str(e)


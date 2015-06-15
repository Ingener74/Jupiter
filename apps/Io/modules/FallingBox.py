#!/usr/bin/env python
#encoding: utf8

import sys
from PySide.QtGui import QApplication, QMessageBox

PLAYER_TITLE = u"Игровой плеер на движке Юпитер"

try:
    import JupiterPython as j
    import Box2DPython as b
except ImportError as e:
    app = QApplication(sys.argv)
    QMessageBox.critical(None, \
                         PLAYER_TITLE, \
                         u'Установи в PYTHONPATH путь до библиотеки _JupiterPython.{so, pyd, dll} и JupiterPython.py', \
                         QMessageBox.Ok | QMessageBox.Default,\
                         QMessageBox.NoButton)
    sys.exit(1)

class Box(j.MoveListener, j.KeyboardListener):
    def __init__(self, window):
        j.MoveListener.__init__(self)
        j.KeyboardListener.__init__(self)
        
        self.window = window

    def move(self, x, y, z):
        pass

    def key(self, key):
        body = j.node2Body(self.getNode()).getPhysicsBody()
        if key == 111 or key == 328:
            body.ApplyForceToCenter(b.b2Vec2(0, 100), True)
        if key == 116 or key == 336:
            body.ApplyForceToCenter(b.b2Vec2(0, -100), True)
        if key == 113 or key == 331:
            body.ApplyForceToCenter(b.b2Vec2(-100, 0), True)
        if key == 114 or key == 333:
            body.ApplyForceToCenter(b.b2Vec2(100, 0), True)
        if key == 57 or key == 65:
            body.ApplyForceToCenter(b.b2Vec2(0, 300), True)

class BoxCollision(j.CollisionListener):
    def __init__(self):
        j.CollisionListener.__init__(self)
        
    def collision(self, node):
        #print u'Я столкнулся с ', node.getName(), u' тег ', node.getTag()
        #self.getBox2dNode().applyForceToCenter(0., 3., True)
        pass

DEG2RAD = 3.1415926 / 180.
RAD2DEG = 180. / 3.1415926

class FallingBox(object):
    
    # WIDTH  = 1000
    WIDTH  = 300
    HEIGTH = WIDTH * 3.0 / 5.0
    
    FPS    = 60.0
    
    GROUND = 2
    
    """
    - Сложная физическая форма из json(отладка)
    - Proxy узлы для отложенной загрузки
    - Надо добавить ещё разных тел с разной формой, в том числе сложной, составной, разрушающейся формой
      и попробовать все Joint'ы, в рамках Ио до остальной разработки Европы
    - Надо сделать 2-й тип элемента рисования на кадрах
    - Анимация
    - Звуки
    - Spine
    - import Tiled, tmx
    - 3D Mesh
    
    На выходные
    - шарниры(joints)
    - подсчёт ссылок
    - стек матриц модели

    Ключевые слова для поиска ресурсов для игр
    * platformer ground sprites
    * car profile sprites/images
    * explosion generators/ генераторы взрывов
    """
    
    def __init__(self, window, width, height):
        
        self.__isReady = False
        
        j.File.setBase('../../samples/Box')
        
        shader = j.FileShader(j.File('Resources/sprite.vs'), j.File('Resources/sprite.fs'))
        #box2dSh = j.FileShader(j.File('Resources/box2d.vs'), j.File('Resources/box2d.fs'))
        
        physics       = j.Physics(1.0 / self.FPS)
        
        camera = j.Camera(j.Perspective(45.0, width * 1. / height * 1., 1.0, 1000.0))
        camera.setPosition(0, 0, -20)#.setRotation(0, 1, 0, -0.3)

        render        = j.RenderVisitor(camera)
        
        rn = j.Node()
        
        bgImage = j.PngImage('Resources/bg.png')
        bg = j.Sprite()
        bg.setProgram(shader).\
            setTexture(j.ImageTexture(bgImage)).\
            setShape(j.ImageShape(bgImage)).\
            translate(0., 0., -1.).\
            setScaleF(0.022)
            
            
        self.boxTest = Box(window)
        self.boxCol = BoxCollision()
        boxImage = j.PngImage('Resources/box.png')
        
        boxDef = b.b2BodyDef()
        boxDef.type = b.b2_dynamicBody;
        boxFixDef = b.b2FixtureDef()
        boxFixDef.density = 1.
        boxFixDef.restitution = .5
        
        boxPhShape = j.PoligonShape(boxImage, boxFixDef)
        
        box1 = j.SpriteBody(physics, boxDef, boxPhShape)
        box1.\
            setProgram(shader).\
            setTexture(j.ImageTexture(boxImage)).\
            setShape(j.ImageShape(boxImage)).\
            setMoveListener(self.boxTest).\
            translate(0, 2, 1).\
            setScaleF(0.002)
        box1.setCollisionListener(self.boxCol)
        
        box2 = j.SpriteBody(box1)
        box2.setScaleF(.0015).setPosition(-4, -2, 1)
         
        box3 = j.SpriteBody(box1)
        box3.setPosition(0, 3, 1).setScaleF(.001)
         
        box4 = j.SpriteBody(box3)
        box4.setPosition(-2, 2, 1)
         
        box5 = j.SpriteBody(box3)
        box5.setPosition(-3, 3, 1)
         
        box6 = j.SpriteBody(box3)
        box6.setScaleF(.002).setPosition(0, 3, 1)
         
        box7 = j.SpriteBody(box6)
        box7.setPosition(4, 3, 1).setRotation(0, 0, 1, 30 * DEG2RAD)
        
        # Сложная форма
        phAtlas = j.PhysicsBodyEditorAtlas(j.File('Resources/Box.json'))

        # Сложная физическая форма
        ship1Image = j.PngImage('Resources/ship1.png')
        
        ship1FixDef = b.b2FixtureDef()
        ship1FixDef.density = 4
        ship1FixDef.restitution = .6
        
        shipComplexShape = j.ComplexShape(ship1Image, phAtlas.getShape('Ship'), ship1FixDef)
        
        ship1Def = b.b2BodyDef()
        ship1Def.type = b.b2_dynamicBody
         
        ship1 = j.SpriteBody(physics, ship1Def, shipComplexShape)
        ship1.setProgram(shader).\
            setTexture(j.ImageTexture(ship1Image)).\
            setShape(j.ImageShape(ship1Image)).\
            setScaleF(0.01).\
            setPosition(3, 3, 1)
        
        # Мячик
        ballDef = b.b2BodyDef()
        ballDef.type = b.b2_dynamicBody
        
        ballFixDef = b.b2FixtureDef()
        ballFixDef.density = 4
        ballFixDef.restitution = 0.7
        
        ballImage = j.PngImage('Resources/ball1.png')
        ballPhShape = j.CircleShape(ballImage, ballFixDef)
        
        ball1 = j.SpriteBody(physics, ballDef, ballPhShape)
        ball1.setProgram(shader).\
            setTexture(j.ImageTexture(ballImage)).\
            setShape(j.ImageShape(ballImage)).\
            setScaleF(0.01).\
            setPosition(-5, 3, 1)

        ball2 = j.SpriteBody(ball1)
        ball2.setPosition(-4, 3, 1)
        ball3 = j.SpriteBody(ball1)
        ball3.setPosition(-5, 4, 1)
        ball4 = j.SpriteBody(ball1)
        ball4.setPosition(-4, 4, 1)
        ball5 = j.SpriteBody(ball1)
        ball5.setPosition(-6, 3, 1)
        ball6 = j.SpriteBody(ball1)
        ball6.setPosition(-6, 4, 1)

        # Пропеллер
        propellerDef = b.b2BodyDef()
        propellerDef.type = b.b2_dynamicBody

        propellerFixDef = b.b2FixtureDef()
        propellerFixDef.density = 1

        propellerImage = j.PngImage('Resources/propeller3.png')

        self.propellerComplexShape = j.ComplexShape(propellerImage, phAtlas.getShape('Propeller3'), propellerFixDef)
        propeller1 = j.SpriteBody(physics, propellerDef, self.propellerComplexShape)
        propeller1.\
            setProgram(shader).\
            setTexture(j.ImageTexture(propellerImage)).\
            setShape(j.ImageShape(propellerImage)).\
            setScaleF(0.002).\
            setPosition(4.6, 3, 0.99)

        propeller2 = j.SpriteBody(propeller1)
        propeller2.setPosition(-4, 8, 0.99)
        
        # Соединим главную коробку и пропеллер
        propBoxDef = b.b2DistanceJointDef()
        propBoxDef.Initialize(box1.getPhysicsBody(), propeller2.getPhysicsBody(), \
            box1.getPhysicsBody().GetPosition(), propeller2.getPhysicsBody().GetPosition())
        propBoxDef.lenght = 1

        propBox = j.DistanceJoint(physics, propBoxDef)

        # Земля
        groundImage = j.PngImage('Resources/ground.png')
        
        groundPhShape = j.PoligonShape(groundImage, b.b2FixtureDef())
        
        groundProto = j.SpriteBody(physics, b.b2BodyDef(), groundPhShape)
        groundProto.setProgram(shader).\
            setTexture(j.ImageTexture(groundImage)).\
            setShape(j.ImageShape(groundImage)).\
            setName('flour').\
            setTag(self.GROUND).\
            setScaleF(0.01)
        
        
        grounds = [j.SpriteBody(groundProto) for i in range(0, 7)]
         
        grounds[0].translate( 2, -8, 0.98)
        grounds[1].translate(-2, -8, 0.98)
        grounds[2].translate( 4, -8, 0.98)
        grounds[3].translate(-4, -8, 0.98)
        grounds[4].translate(-7.5, -7.3, 0.98).setRotation(0, 0, 1, (360 - 30) * DEG2RAD)
        grounds[5].translate( 7.5, -7.3, 0.98).setRotation(0, 0, 1,  30 * DEG2RAD)

        grounds[6].translate(6, 3, 0.98).setRotation(0, 0, 1,  45 * DEG2RAD)

        # Приделаем пропеллер к одной из земель
        propJointDef = b.b2RevoluteJointDef()
        propJointDef.Initialize(propeller1.getPhysicsBody(), grounds[6].getPhysicsBody(), b.b2Vec2(4.6, 2.7))
        propellerJoint = j.RevoluteJoint(physics, propJointDef)

        # Машина
        carBodyDef = b.b2BodyDef()
        carBodyDef.type = b.b2_dynamicBody

        carFixtureDef = b.b2FixtureDef()
        carFixtureDef.density = 3

        carImage = j.PngImage('Resources/car.png')

        carShape = j.ComplexShape(carImage, phAtlas.getShape('Car'), carFixtureDef)

        car = j.SpriteBody(physics, carBodyDef, carShape)
        car.setProgram(shader).\
            setTexture(j.ImageTexture(carImage)).\
            setShape(j.ImageShape(carImage)).\
            setScaleF(0.01)

        # Добавляем все узлы в дерево
        rn.\
            addNode(bg).\
            addNode(grounds[0]).\
            addNode(grounds[1]).\
            addNode(grounds[2]).\
            addNode(grounds[3]).\
            addNode(grounds[4]).\
            addNode(grounds[5]).\
            addNode(grounds[6]).\
            addNode(box1).\
            addNode(box2).\
            addNode(box3).\
            addNode(box4).\
            addNode(box5).\
            addNode(box6).\
            addNode(box7).\
            addNode(ball1).\
            addNode(ball2).\
            addNode(ball3).\
            addNode(ball4).\
            addNode(ball5).\
            addNode(ball6).\
            addNode(propeller1).\
            addNode(propeller2).\
            addNode(ship1).\
            addNode(propellerJoint).\
            addNode(propBox).\
            addNode(car)

        self.game = j.Game()
        self.game.\
            setRootNode(rn).\
            addVisitor(physics).\
            addVisitor(render).\
            addKeyboardListener(self.boxTest).\
            setWidth(width).\
            setHeight(height)

        self.__isReady = True
    
    def isReady(self):
        return self.__isReady

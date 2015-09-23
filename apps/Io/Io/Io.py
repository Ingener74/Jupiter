#!/usr/bin/env python
# encoding: utf8

import sys

from PySide.QtGui import QApplication, QMessageBox

PLAYER_TITLE = u"Игровой плеер на движке Юпитер"

# noinspection PyUnresolvedReferences
try:
    import JupiterPython as j
    import Box2DPython as b
    # from glmPython import vec3
except ImportError as e:
    app = QApplication(sys.argv)

    print u'Oшибка ', str(e)

    QMessageBox.critical(None,
                         PLAYER_TITLE,
                         u'Установи в PYTHONPATH путь до библиотеки _JupiterPython.{so, pyd, dll} и JupiterPython.py ',
                         QMessageBox.Ok | QMessageBox.Default,
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
        pass


DEG2RAD = 3.1415926 / 180.
RAD2DEG = 180. / 3.1415926


# noinspection PyPep8Naming
class Io(object):

    WIDTH = 1024
    HEIGHT = WIDTH * 3.0 / 5.0

    FPS = 60.0

    GROUND = 2

    """
    - Сложная физическая форма из json(отладка)
    - Надо добавить ещё разных тел с разной формой, в том числе сложной, составной, разрушающейся формой
      и попробовать все Joint'ы, в рамках Ио до остальной разработки Европы
    - Звуки
    - Spine
    - import Tiled, tmx
    - 3D Mesh

    Ключевые слова для поиска ресурсов для игр
    * platformer ground sprites
    * car profile sprites/images
    * explosion generators/ генераторы взрывов
    """

    def __init__(self, window, width, height):

        self.__isReady = False

        j.File.setBase('../../../samples/Box')

        shader = j.FileShader(j.File('Resources/sprite.vs'), j.File('Resources/sprite.fs'))
        # box2dSh = j.FileShader(j.File('Resources/box2d.vs'), j.File('Resources/box2d.fs'))

        # Атлас физических форм
        phAtlas = j.PhysicsBodyEditorAtlas(j.File('Resources/Box.json'))

        physics = j.Physics(1.0 / self.FPS)
        render = j.RenderVisitor()

        rn = j.Node()

        cameraTrans = j.Transform(0, 0, -20)

        camera = j.Camera(cameraTrans, j.Perspective(45.0, width * 1. / height * 1., 1.0, 1000.0))

        rn.addNode(camera)

        camera.addNode(cameraTrans)

        background = j.Transform()
        background.translate(0, 0, -1).setScaleF(0.022)

        bgImage = j.PngImage('Resources/bg.png')
        background.addNode(j.Sprite(j.ImageTexture(bgImage), j.ImageShape(bgImage), shader))

        # Ящик
        self.boxTest = Box(window)
        boxImage = j.PngImage('Resources/box.png')

        boxDef = b.b2BodyDef()
        boxDef.type = b.b2_dynamicBody

        boxFixDef = b.b2FixtureDef()
        boxFixDef.density = 1.
        boxFixDef.restitution = .5

        boxPhShape = j.PoligonShape(boxImage, boxFixDef)

        box1 = j.Transform(0, 6, 1)
        box1.\
            setScaleF(0.002).\
            addNode(j.Body(physics, boxDef, boxPhShape)).\
            addNode(j.Sprite(j.ImageTexture(boxImage), j.ImageShape(boxImage), shader))
        # box1.setScaleF(0.002)

        box2 = j.Transform(box1)
        box2.translateX(6).rotateZ(0.3)

        box3 = j.Transform(box1)
        box3.setPosition(0, 3, 1)

        box4 = j.Transform(box3)
        box4.setPosition(-2, 2, 1)

        box5 = j.Transform(box3)
        box5.setPosition(-3, 3, 1)

        box6 = j.Transform(box3)
        box6.setPosition(0, 3, 1)

        box7 = j.Transform(box6)
        box7.setPosition(4, 3, 1).setRotation(0, 0, 1, 30 * DEG2RAD)

        # Сложная физическая форма, космический корабль
        ship1Image = j.PngImage('Resources/ship1.png')

        ship1FixDef = b.b2FixtureDef()
        ship1FixDef.density = 4
        ship1FixDef.restitution = .6

        shipComplexShape = j.ComplexShape(ship1Image, phAtlas.getShape('Ship'), ship1FixDef)

        ship1Def = b.b2BodyDef()
        ship1Def.type = b.b2_dynamicBody

        ship1 = j.Transform(3, 3, 1)
        ship1.\
            setScaleF(0.01).\
            addNode(j.Body(physics, ship1Def, shipComplexShape)).\
            addNode(j.Sprite(j.ImageTexture(ship1Image), j.ImageShape(ship1Image), shader))

        # Мячики
        ballDef = b.b2BodyDef()
        ballDef.type = b.b2_dynamicBody

        ballFixDef = b.b2FixtureDef()
        ballFixDef.density = 4
        ballFixDef.restitution = 0.7

        ballImage = j.PngImage('Resources/ball1.png')
        ballPhShape = j.CircleShape(ballImage, ballFixDef)

        ball1 = j.Transform(-5, 3, 1)
        ball1.\
            setScaleF(.01).\
            addNode(j.Body(physics, ballDef, ballPhShape)).\
            addNode(j.Sprite(j.ImageTexture(ballImage), j.ImageShape(ballImage), shader))

        ball2 = j.Transform(ball1)
        ball2.setPosition(-4, 3, 1)
        ball3 = j.Transform(ball1)
        ball3.setPosition(-5, 4, 1)
        ball4 = j.Transform(ball1)
        ball4.setPosition(-4, 4, 1)
        ball5 = j.Transform(ball1)
        ball5.setPosition(-6, 3, 1)
        ball6 = j.Transform(ball1)
        ball6.setPosition(-6, 4, 1)

        # # Пропеллер
        propellerDef = b.b2BodyDef()
        propellerDef.type = b.b2_dynamicBody

        propellerFixDef = b.b2FixtureDef()
        propellerFixDef.density = 1

        propellerImage = j.PngImage('Resources/propeller3.png')

        propellerComplexShape = j.ComplexShape(propellerImage, phAtlas.getShape('Propeller3'), propellerFixDef)
        propeller1 = j.Transform(4.6, 3, 0.99)
        propeller1.\
            setScaleF(.002).\
            addNode(j.Body(physics, propellerDef, propellerComplexShape)).\
            addNode(j.Sprite(j.ImageTexture(propellerImage), j.ImageShape(propellerImage), shader))

        propeller2 = j.Transform(propeller1)
        propeller2.setPosition(-4, 8, 0.99)

        # Соединим главную коробку и пропеллер
        # propBoxDef = b.b2DistanceJointDef()
        # propBoxDef.Initialize(box1.getPhysicsBody(), propeller2.getPhysicsBody(),
        #                       box1.getPhysicsBody().GetPosition(), propeller2.getPhysicsBody().GetPosition())
        # propBoxDef.lenght = 1
        #
        # propBox = j.DistanceJoint(physics, propBoxDef)

        # Земля
        groundImage = j.PngImage('Resources/ground.png')

        groundPhShape = j.PoligonShape(groundImage, b.b2FixtureDef())

        groundProto = j.Transform(0, 0, 0.98)
            # setScaleF(0.01).\
        groundProto.setScaleF(0.01)
        groundProto.\
            addNode(j.Body(physics, b.b2BodyDef(), groundPhShape)).\
            addNode(j.Sprite(j.ImageTexture(groundImage), j.ImageShape(groundImage), shader))

        grounds = []
        for i in range(0, 7):
            grounds.append(j.Transform(groundProto))

        grounds[0].translate(2, -8, 0)
        grounds[1].translate(-2, -8, 0)
        grounds[2].translate(4, -8, 0)
        grounds[3].translate(-4, -8, 0)
        grounds[4].translate(-7.5, -7.3, 0).setRotation(0, 0, 1, (360 - 30) * DEG2RAD)
        grounds[5].translate(7.5, -7.3, 0).setRotation(0, 0, 1,  30 * DEG2RAD)

        grounds[6].translate(6, 3, 0).setRotation(0, 0, 1,  45 * DEG2RAD)

        # Булава для тестирования стека матриц модели
        cudgelImage = j.PngImage('Resources/cudgel.png')

        cudgel = j.Transform(800, -4, 0.1)
        cudgel.rotateZ(-90 * DEG2RAD)
        cudgel.translateX(20)
        cudgel.setScaleF(4)
        cudgel.addNode(j.Sprite(j.ImageTexture(cudgelImage), j.ImageShape(cudgelImage), shader))

        box1.addNode(cudgel)

        # Приделаем пропеллер к одной из земель
        # propJointDef = b.b2RevoluteJointDef()
        # propJointDef.Initialize(propeller1.getPhysicsBody(), grounds[6].getPhysicsBody(), b.b2Vec2(4.6, 2.7))
        # propellerJoint = j.RevoluteJoint(physics, propJointDef)

        # Машина
        # carBodyDef = b.b2BodyDef()
        # carBodyDef.type = b.b2_dynamicBody

        # carFixtureDef = b.b2FixtureDef()
        # carFixtureDef.density = 3

        # carImage = j.PngImage('Resources/car.png')

        # carShape = j.ComplexShape(carImage, phAtlas.getShape('Car'), carFixtureDef)

        # car = j.SpriteBody(physics, carBodyDef, carShape)
        # car.setProgram(shader).\
        #     setTexture(j.ImageTexture(carImage)).\
        #     setShape(j.ImageShape(carImage)).\
        #     setScaleF(0.01)

        # Добавляем все узлы в дерево

        camera.addNode(background).\
            addNode(groundProto).\
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
            addNode(ship1).\
            addNode(propeller1).\
            addNode(propeller2)

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

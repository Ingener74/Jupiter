#!/usr/bin/env python
#encoding: utf8

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
        body = j.node2Box2dNode(self.getNode()).getPhysicsBody()
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
    
    WIDTH  = 800
    HEIGTH = WIDTH * 3.0 / 5.0
    
    FPS    = 60.0
    
    GROUND = 2
    
    """
    - Камера через положение и ориентацию/кватернион
    - Сложная физическая форма из json
    - Надо добавить ещё разных тел с разной формой, в том числе сложной, составной, разрушающейся формой
      и попробовать все Joint'ы, в рамках Ио до остальной разработки Европы
    - Надо сделать 2-й тип элемента рисования на кадрах
    - Анимация
    - Звуки
    - Spine
    - import Tiled, tmx
    - 3D Mesh
    
    На выходные
    - камера через положение и кватернион
    - шарниры(joints)
    - подсчёт ссылок
    """
    
    def __init__(self, window, width, height):
        
        self.__isReady = False
        
        j.File.setBase('../../samples/Box')
        
        self.shader = j.FileShader(j.File('Resources/sprite.vs'), j.File('Resources/sprite.fs'))
        #self.box2dSh = j.FileShader(j.File('Resources/box2d.vs'), j.File('Resources/box2d.fs'))
        
        self.camera = j.Camera(j.Perspective(45.0, width * 1. / height * 1., 1.0, 1000.0), \
                               j.Vec3(0.0, 0.0, 18.0),                                     \
                               j.Vec3(0.0, 0.0, 0.0),                                      \
                               j.Vec3(0.0, 1.0, 0.0))
        
        
        self.printVisitor  = j.PrintVisitor()
        self.physics       = j.Box2dVisitor(1.0 / self.FPS)
        self.render        = j.RenderVisitor(self.camera)
        
        self.rn = j.Node()
        
        bgImage = j.PngImage('Resources/bg.png')
        self.bgTexture = j.ImageTexture(bgImage)
        self.bgShape = j.ImageShape(bgImage)
        self.bg = j.Sprite()
        self.bg.\
            setProgram(self.shader).\
            setTexture(self.bgTexture).\
            setShape(self.bgShape).\
            translate(0., 0., -1.).\
            setScaleF(0.02)
            
            
        self.boxTest = Box(window)
        self.boxCol = BoxCollision()
        boxImage = j.PngImage('Resources/box.png')
        self.boxTex = j.ImageTexture(boxImage)
        self.boxShape = j.ImageShape(boxImage)
        
        boxDef = b.b2BodyDef()
        boxDef.type = b.b2_dynamicBody;
        boxFixDef = b.b2FixtureDef()
        boxFixDef.density = 1.
        boxFixDef.restitution = .5
        
        boxPhShape = j.PoligonShape(boxImage, boxFixDef)
        
        self.box1 = j.SpriteBox2d(self.physics, boxDef, boxPhShape)
        self.box1.\
            setProgram(self.shader).\
            setTexture(self.boxTex).\
            setShape(self.boxShape).\
            setMoveListener(self.boxTest).\
            translate(0, 2, 1).\
            setScaleF(0.002)
        self.box1.setCollisionListener(self.boxCol)
        
        self.box2 = j.SpriteBox2d(self.box1)
        self.box2.setScaleF(.0015).setPosition(-4, -2, 1)
         
        self.box3 = j.SpriteBox2d(self.box1)
        self.box3.setPosition(0, 3, 1).setScaleF(.001)
         
        self.box4 = j.SpriteBox2d(self.box3)
        self.box4.setPosition(-2, 2, 1)
         
        self.box5 = j.SpriteBox2d(self.box3)
        self.box5.setPosition(-3, 3, 1)
         
        self.box6 = j.SpriteBox2d(self.box3)
        self.box6.setScaleF(.002).setPosition(0, 3, 1)
         
        self.box7 = j.SpriteBox2d(self.box6)
        self.box7.setPosition(4, 3, 1).setRotation(0, 0, 1, 30 * DEG2RAD)
        
        # Сложная физическая форма
        ship1Image = j.PngImage('Resources/ship1.png')
        self.ship1Tex = j.ImageTexture(ship1Image)
        self.ship1Shape = j.ImageShape(ship1Image)
        
        ship1FixDef = b.b2FixtureDef()
        ship1FixDef.density = 4
        ship1FixDef.restitution = .6
        
        self.boxComplexShape = j.ComplexShape(ship1Image, j.File('Resources/Box.json'), 'Ship', ship1FixDef)
        
        ship1Def = b.b2BodyDef()
        ship1Def.type = b.b2_dynamicBody
         
        self.ship1 = j.SpriteBox2d(self.physics, ship1Def, self.boxComplexShape)
        self.ship1.setProgram(self.shader).\
            setTexture(self.ship1Tex).\
            setShape(self.ship1Shape).\
            setScaleF(0.01).\
            setPosition(3, 3, 1)
        
        # Мячик
        ballImage = j.PngImage('Resources/ball1.png')
        self.ballTex = j.ImageTexture(ballImage)
        self.ballShape = j.ImageShape(ballImage)
        
        ballDef = b.b2BodyDef()
        ballDef.type = b.b2_dynamicBody
        ballFixDef = b.b2FixtureDef()
        ballFixDef.density = 4
        ballFixDef.restitution = 0.7
        
        ballPhShape = j.CircleShape(ballImage, ballFixDef)
        
        self.ball = j.SpriteBox2d(self.physics, ballDef, ballPhShape)
        self.ball.setProgram(self.shader).\
            setTexture(self.ballTex).\
            setShape(self.ballShape).\
            setScaleF(0.01).\
            setPosition(-5, 3, 1)

        self.ball2 = j.SpriteBox2d(self.ball)
        self.ball2.setPosition(-4, 3, 1)
        self.ball3 = j.SpriteBox2d(self.ball)
        self.ball3.setPosition(-5, 4, 1)
        self.ball4 = j.SpriteBox2d(self.ball)
        self.ball4.setPosition(-4, 4, 1)
        self.ball5 = j.SpriteBox2d(self.ball)
        self.ball5.setPosition(-6, 3, 1)
        self.ball6 = j.SpriteBox2d(self.ball)
        self.ball6.setPosition(-6, 4, 1)

        # Пропеллер
        propellerImage = j.PngImage('Resources/propeller3.png')
        self.propellerTex = j.ImageTexture(propellerImage)
        self.propellerShape = j.ImageShape(propellerImage)

        propellerDef = b.b2BodyDef()
        propellerDef.type = b.b2_dynamicBody

        propellerFixDef = b.b2FixtureDef()
        propellerFixDef.density = 1

        self.propellerComplexShape = j.ComplexShape(propellerImage, j.File('Resources/Box.json'), 'Propeller3', propellerFixDef)
        self.propeller = j.SpriteBox2d(self.physics, propellerDef, self.propellerComplexShape)
        self.propeller.\
            setProgram(self.shader).\
            setTexture(self.propellerTex).\
            setShape(self.propellerShape).\
            setScaleF(0.002).\
            setPosition(5, 8, 0.99)

        self.propeller2 = j.SpriteBox2d(self.propeller)
        self.propeller2.setPosition(-4, 8, 0.99)

        # Земля
        groundImage = j.PngImage('Resources/ground.png')
        self.groundTex = j.ImageTexture(groundImage)
        self.groundShape = j.ImageShape(groundImage)
        
        groundPhShape = j.PoligonShape(groundImage, b.b2FixtureDef())
        
        groundProto = j.SpriteBox2d(self.physics, b.b2BodyDef(), groundPhShape)
        groundProto.setProgram(self.shader).\
            setTexture(self.groundTex).\
            setShape(self.groundShape).\
            setName('flour').\
            setTag(self.GROUND).\
            setScaleF(0.01)
        
        
        self.grounds = [j.SpriteBox2d(groundProto) for i in range(0, 7)]
         
        self.grounds[0].translate( 2, -8, 1)
        self.grounds[1].translate(-2, -8, 1)
        self.grounds[2].translate( 4, -8, 1)
        self.grounds[3].translate(-4, -8, 1)
        self.grounds[4].translate(-7.5, -7.3, 1).setRotation(0, 0, 1, (360 - 30) * DEG2RAD)
        self.grounds[5].translate( 7.5, -7.3, 1).setRotation(0, 0, 1,  30 * DEG2RAD)
 
        self.grounds[6].translate(6, 3, 1).setRotation(0, 0, 1,  45 * DEG2RAD)
        
        self.rn.\
            addNode(self.bg).\
            addNode(self.grounds[0]).\
            addNode(self.grounds[1]).\
            addNode(self.grounds[2]).\
            addNode(self.grounds[3]).\
            addNode(self.grounds[4]).\
            addNode(self.grounds[5]).\
            addNode(self.grounds[6]).\
            addNode(self.box1).\
            addNode(self.box2).\
            addNode(self.box3).\
            addNode(self.box4).\
            addNode(self.box5).\
            addNode(self.box6).\
            addNode(self.box7).\
            addNode(self.ball).\
            addNode(self.ball2).\
            addNode(self.ball3).\
            addNode(self.ball4).\
            addNode(self.ball5).\
            addNode(self.ball6).\
            addNode(self.propeller).\
            addNode(self.propeller2).\
            addNode(self.ship1)
        
            #addVisitor(self.printVisitor).\
        self.game = j.Game()
        self.game.setRootNode(self.rn).\
            addVisitor(self.physics).\
            addVisitor(self.render).\
            addKeyboardListener(self.boxTest).\
            setWidth(width).\
            setHeight(height)

        self.__isReady = True
    
    def isReady(self):
        return self.__isReady

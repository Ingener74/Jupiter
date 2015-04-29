#!/usr/bin/env python
# -*- coding: utf-8 -*-

from OpenGL.GL   import *
from OpenGL.GLU  import *
from OpenGL.GLUT import *
import sys
import math

# Установи в PYTHONPATH путь до библеотеки _Jupiter.{so, pyd, dll} и PyJupiter.py
import PyJupiter as j

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


def init ():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_TEXTURE_2D)


def reshape ( width, height ):
    glViewport(0, 0, width, height)


def display ():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    global falling_box
    falling_box.getGame().draw()
    
    glutSwapBuffers()


def keyPressed (*args):
    if args [0] == '\033':
        sys.exit ()


def animate():
    glutPostRedisplay ()


def mouse( button, state, x, y ):
#     global game
#     game.input()
    pass


def main():
    
    print "Jupiter Python Game Player"
    
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(800, 600)
    glutInitWindowPosition(0, 0)
    
    glutCreateWindow("Jupiter game player")
    glutDisplayFunc(display)
    glutIdleFunc(animate)
    glutReshapeFunc(reshape)
    glutKeyboardFunc(keyPressed)
    glutMouseFunc(mouse)
    
    init()
    
    
    global falling_box
    falling_box = FallingBox()
    
    
    glutMainLoop()


if __name__ == '__main__':
    try:
        main()
    except j.JupiterError as e:
        print e.what()
    except Exception as e:
        print str(e)








#!/usr/bin/env python
# -*- coding: utf-8 -*-

from OpenGL.GL   import *
from OpenGL.GLU  import *
from OpenGL.GLUT import *
import sys
import math

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../build/wrappers')))
import PyJupiter as j

# class BackGround(j.Controller):
#     def __init__(self):
#         j.Controller.__init__(self)
#         
#     def update(self, elapsedTime):
#         pass

def init ():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_TEXTURE_2D)

def reshape ( width, height ):
    glViewport(0, 0, width, height)

def display ():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
#     global game
#     game.draw()
    
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
    
    gameFile = "../../samples/Asteroids/Asteroids.json"
    
    j.File.setBufferFactory(j.LinuxFileFactory())
    
    global game
    game = j.JsonGame(gameFile)
#     
#     c = j.Controller()
#     
#     s = j.Sprite("resources/images/bg.png")
#     s.translateX(1.0)
#     
#     print s.getTexture().bind()
#     print s.getController().update(60.0 / 1000.0)
    
    init()
    
    glutMainLoop()

if __name__ == '__main__':
    try:
        main()
    except j.JupiterError as e:
        print e.what()
    except Exception as e:
        print str(e)








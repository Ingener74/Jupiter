#/usr/bin/env python
#encoding: utf8

import sys

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

WIDTH = 200
HEIGHT = WIDTH * 3 / 5
#PLAYER_TITLE = u"Игровой плеер на движке Юпитер"
PLAYER_TITLE = 'Jupiter game player'

def display():
    glClearColor(0.1, 0.3, 0.1, 1.0)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    glutSwapBuffers()

def special(key, x, y):
    print key

def keyboard(key, x, y):
    #if key == GLUT_KEY_F1:
    glutLeaveMainLoop()

if __name__ == '__main__':
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH)
    glutInitWindowSize(WIDTH, HEIGHT)
    glutCreateWindow(PLAYER_TITLE)
    
    glutDisplayFunc(display)
    glutSpecialFunc(special)
    glutKeyboardFunc(keyboard)
    
    glutMainLoop()
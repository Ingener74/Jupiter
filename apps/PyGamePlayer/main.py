#!/usr/bin/env python
# -*- coding: utf-8 -*-

from OpenGL.GL   import *
from OpenGL.GLU  import *
from OpenGL.GLUT import *
import sys
import math

def init ():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_TEXTURE_2D)

def reshape ( width, height ):
    glViewport(0, 0, width, height)

def display ():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glutSwapBuffers()

def keyPressed (*args):
    if args [0] == '\033':
        sys.exit ()

def animate():
    glutPostRedisplay ()

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(800, 600)
    glutInitWindowPosition(0, 0)
    
    glutCreateWindow("Jupiter game player")
    glutDisplayFunc(display)
    glutIdleFunc(animate)
    glutReshapeFunc(reshape)
    glutKeyboardFunc(keyPressed)
    init()
    
    glutMainLoop()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print str(e)

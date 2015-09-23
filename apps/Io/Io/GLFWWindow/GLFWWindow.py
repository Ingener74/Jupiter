# -*- coding: utf-8 -*-
from PySide.QtCore import Signal, QObject

from glfwPython import *
from OpenGL.GL import *
from Io import Io, j, WIDTH, HEIGHT, PLAYER_TITLE


class GLFWWindow(QObject):
    on_close = Signal(object)

    def __init__(self):
        QObject.__init__(self)
        self.fallingBox = None

    def show(self):

        print WIDTH, HEIGHT

        # Initialize the library
        if not glfwInit():
            return False

        # glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3)
        # glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3)
        # glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)
        # glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_FORWARD_COMPAT)

        # Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(WIDTH, HEIGHT, "", None, None)
        if not window:
            glfwTerminate()
            return False

        # Make the window's context current
        glfwMakeContextCurrent(window)

        print 'OpenGL Version:                  ', glGetString(GL_VERSION)
        print 'OpenGL Shading Language Version: ', glGetString(GL_SHADING_LANGUAGE_VERSION)
        print 'OpenGL Vendor:                   ', glGetString(GL_VENDOR)
        print 'OpenGL Renderer:                 ', glGetString(GL_RENDERER)

        # Limit the frameRate to 60fps.
        glfwSwapInterval(1)

        glViewport(0, 0, WIDTH, HEIGHT)
        glEnable(GL_TEXTURE_2D)
        glEnable(GL_DEPTH_TEST)
        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

        try:
            j.startJupiter()
            self.fallingBox = Io(self)

            # self.startTimer(1000.0 / self.fallingBox.FPS)

        except RuntimeError, e:
            raise SystemExit(u'Ошибка старта ' + str(e).decode('utf-8'))

        # Loop until the user closes the window
        while not glfwWindowShouldClose(window):
            # /* Render here */
            glClearColor(0.1, 0.3, 0.1, 1.0)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

            try:
                if self.fallingBox and self.fallingBox.isReady():
                    self.fallingBox.game.draw()

            except RuntimeError, e:
                raise SystemExit(str(e))


            # Swap front and back buffers
            glfwSwapBuffers(window)

            # Poll for and process events
            glfwPollEvents()

        glfwTerminate()
        return True

    def close(self):
        j.endJupiter()
        self.on_close.emit(None)

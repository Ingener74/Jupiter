# -*- coding: utf-8 -*-
from PySide.QtGui import QWidget

from Io import OpenGLWidget, GLFWWindow
from SelectImplementation import Ui_SelectImpl


class Select(QWidget, Ui_SelectImpl):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)

        self.glfw_window = GLFWWindow.GLFWWindow()
        # self.glfw_window.on_close.connect(self.glfwClose)

        self.PySideButton.clicked.connect(self.pySide)
        self.FreeGlutButton.clicked.connect(self.glut)
        self.GLFWButton.clicked.connect(self.onGLFW)

    def pySide(self):
        window = OpenGLWidget()
        window.show()
        self.close()

    def onGLFW(self):
        self.hide()
        self.glfw_window.show()

    def glfwClose(self):
        self.close()

    def glut(self):
        pass

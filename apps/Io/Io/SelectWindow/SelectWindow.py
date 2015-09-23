# -*- coding: utf-8 -*-
from PySide.QtGui import QWidget

from Io import OpenGLWidget, GLFWWindow
from SelectImplementation import Ui_SelectImpl


class Select(QWidget, Ui_SelectImpl):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)

        self.pyside_window = OpenGLWidget()
        self.pyside_window.on_close.connect(self.close)

        self.glfw_window = GLFWWindow.GLFWWindow()
        self.glfw_window.on_close.connect(self.close)

        self.PySideButton.clicked.connect(self.startPySide)
        self.FreeGlutButton.clicked.connect(self.startGLUT)
        self.GLFWButton.clicked.connect(self.startGLFW)

    def startPySide(self):
        self.hide()
        self.pyside_window.show()

    def startGLFW(self):
        self.hide()
        self.glfw_window.show()

    def startGLUT(self):
        self.close()

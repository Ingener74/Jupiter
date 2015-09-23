# -*- coding: utf-8 -*-
from PySide.QtGui import QWidget

from Io import OpenGLWidget
from SelectImplementation import Ui_SelectImpl


class Select(QWidget, Ui_SelectImpl):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)

        self.PySideButton.clicked.connect(self.pySide)
        self.FreeGlutButton.clicked.connect(self.glut)
        self.GLFWButton.clicked.connect(self.onGLFW)

    def pySide(self):
        window = OpenGLWidget()
        window.show()
        self.close()

    def onGLFW(self):
        pass

    def glut(self):
        pass

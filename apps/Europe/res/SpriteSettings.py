# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:/Users/Pavel/workspace/Jupiter/apps/Europe/res/SpriteSettings.ui'
#
# Created: Thu Jul 02 00:39:38 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_SpriteSettings(object):
    def setupUi(self, SpriteSettings):
        SpriteSettings.setObjectName("SpriteSettings")
        SpriteSettings.resize(369, 189)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/stationery.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        SpriteSettings.setWindowIcon(icon)
        self.verticalLayout = QtGui.QVBoxLayout(SpriteSettings)
        self.verticalLayout.setObjectName("verticalLayout")
        self.textureGroupBox = QtGui.QGroupBox(SpriteSettings)
        self.textureGroupBox.setObjectName("textureGroupBox")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.textureGroupBox)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.texture = QtGui.QComboBox(self.textureGroupBox)
        self.texture.setObjectName("texture")
        self.verticalLayout_2.addWidget(self.texture)
        self.verticalLayout.addWidget(self.textureGroupBox)
        self.shapeGroupBox = QtGui.QGroupBox(SpriteSettings)
        self.shapeGroupBox.setObjectName("shapeGroupBox")
        self.verticalLayout_3 = QtGui.QVBoxLayout(self.shapeGroupBox)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.shape = QtGui.QComboBox(self.shapeGroupBox)
        self.shape.setObjectName("shape")
        self.verticalLayout_3.addWidget(self.shape)
        self.verticalLayout.addWidget(self.shapeGroupBox)
        self.shaderGroupBox = QtGui.QGroupBox(SpriteSettings)
        self.shaderGroupBox.setObjectName("shaderGroupBox")
        self.verticalLayout_4 = QtGui.QVBoxLayout(self.shaderGroupBox)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.shader = QtGui.QComboBox(self.shaderGroupBox)
        self.shader.setObjectName("shader")
        self.verticalLayout_4.addWidget(self.shader)
        self.verticalLayout.addWidget(self.shaderGroupBox)

        self.retranslateUi(SpriteSettings)
        QtCore.QMetaObject.connectSlotsByName(SpriteSettings)

    def retranslateUi(self, SpriteSettings):
        SpriteSettings.setWindowTitle(QtGui.QApplication.translate("SpriteSettings", "Настройки спрайта", None, QtGui.QApplication.UnicodeUTF8))
        self.textureGroupBox.setTitle(QtGui.QApplication.translate("SpriteSettings", "Текстура", None, QtGui.QApplication.UnicodeUTF8))
        self.shapeGroupBox.setTitle(QtGui.QApplication.translate("SpriteSettings", "Форма", None, QtGui.QApplication.UnicodeUTF8))
        self.shaderGroupBox.setTitle(QtGui.QApplication.translate("SpriteSettings", "Программа", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc

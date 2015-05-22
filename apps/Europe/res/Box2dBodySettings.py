# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:/Users/Pavel/workspace/Jupiter/apps/PyGameDesigner/res/Box2dBodySettings.ui'
#
# Created: Wed May 20 23:36:19 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_Box2dBodySettings(object):
    def setupUi(self, Box2dBodySettings):
        Box2dBodySettings.setObjectName("Box2dBodySettings")
        Box2dBodySettings.resize(314, 71)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/stationery.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Box2dBodySettings.setWindowIcon(icon)
        self.verticalLayout = QtGui.QVBoxLayout(Box2dBodySettings)
        self.verticalLayout.setObjectName("verticalLayout")
        self.shapeGroupBox = QtGui.QGroupBox(Box2dBodySettings)
        self.shapeGroupBox.setObjectName("shapeGroupBox")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.shapeGroupBox)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.comboBox = QtGui.QComboBox(self.shapeGroupBox)
        self.comboBox.setObjectName("comboBox")
        self.verticalLayout_2.addWidget(self.comboBox)
        self.verticalLayout.addWidget(self.shapeGroupBox)

        self.retranslateUi(Box2dBodySettings)
        QtCore.QMetaObject.connectSlotsByName(Box2dBodySettings)

    def retranslateUi(self, Box2dBodySettings):
        Box2dBodySettings.setWindowTitle(QtGui.QApplication.translate("Box2dBodySettings", "Настройки физического тела", None, QtGui.QApplication.UnicodeUTF8))
        self.shapeGroupBox.setTitle(QtGui.QApplication.translate("Box2dBodySettings", "Физическая форма", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc

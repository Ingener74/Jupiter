# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:/Users/Pavel/workspace/Jupiter/apps/IoGamePlayer/res/SelectImplementation.ui'
#
# Created: Thu May 21 20:25:48 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_SelectImpl(object):
    def setupUi(self, SelectImpl):
        SelectImpl.setObjectName("SelectImpl")
        SelectImpl.resize(304, 90)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/main.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        SelectImpl.setWindowIcon(icon)
        self.gridLayout = QtGui.QGridLayout(SelectImpl)
        self.gridLayout.setObjectName("gridLayout")
        self.PySideButton = QtGui.QPushButton(SelectImpl)
        self.PySideButton.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/pysidelogo.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.PySideButton.setIcon(icon1)
        self.PySideButton.setIconSize(QtCore.QSize(128, 64))
        self.PySideButton.setObjectName("PySideButton")
        self.gridLayout.addWidget(self.PySideButton, 0, 0, 1, 1)
        self.FreeGlutButton = QtGui.QPushButton(SelectImpl)
        self.FreeGlutButton.setText("")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/freeglut_logo.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.FreeGlutButton.setIcon(icon2)
        self.FreeGlutButton.setIconSize(QtCore.QSize(128, 64))
        self.FreeGlutButton.setObjectName("FreeGlutButton")
        self.gridLayout.addWidget(self.FreeGlutButton, 0, 1, 1, 1)

        self.retranslateUi(SelectImpl)
        QtCore.QMetaObject.connectSlotsByName(SelectImpl)

    def retranslateUi(self, SelectImpl):
        SelectImpl.setWindowTitle(QtGui.QApplication.translate("SelectImpl", "Выбери реализацию", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc

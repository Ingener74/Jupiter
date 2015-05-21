# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:/Users/Pavel/workspace/Jupiter/apps/IoGamePlayer/res/move.ui'
#
# Created: Thu May 21 22:17:56 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_MoveDialog(object):
    def setupUi(self, MoveDialog):
        MoveDialog.setObjectName("MoveDialog")
        MoveDialog.resize(212, 226)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/main.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MoveDialog.setWindowIcon(icon)
        self.verticalLayout = QtGui.QVBoxLayout(MoveDialog)
        self.verticalLayout.setObjectName("verticalLayout")
        self.comboBoxValue = QtGui.QComboBox(MoveDialog)
        self.comboBoxValue.setObjectName("comboBoxValue")
        self.comboBoxValue.addItem("")
        self.comboBoxValue.addItem("")
        self.comboBoxValue.addItem("")
        self.verticalLayout.addWidget(self.comboBoxValue)
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.pushButtonRight = QtGui.QPushButton(MoveDialog)
        self.pushButtonRight.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/forward.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButtonRight.setIcon(icon1)
        self.pushButtonRight.setIconSize(QtCore.QSize(48, 48))
        self.pushButtonRight.setObjectName("pushButtonRight")
        self.gridLayout.addWidget(self.pushButtonRight, 1, 2, 1, 1)
        self.pushButtonLeft = QtGui.QPushButton(MoveDialog)
        self.pushButtonLeft.setText("")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/back.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButtonLeft.setIcon(icon2)
        self.pushButtonLeft.setIconSize(QtCore.QSize(48, 48))
        self.pushButtonLeft.setObjectName("pushButtonLeft")
        self.gridLayout.addWidget(self.pushButtonLeft, 1, 0, 1, 1)
        self.pushButtonUp = QtGui.QPushButton(MoveDialog)
        self.pushButtonUp.setText("")
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/up.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButtonUp.setIcon(icon3)
        self.pushButtonUp.setIconSize(QtCore.QSize(48, 48))
        self.pushButtonUp.setObjectName("pushButtonUp")
        self.gridLayout.addWidget(self.pushButtonUp, 0, 1, 1, 1)
        self.pushButtonDown = QtGui.QPushButton(MoveDialog)
        self.pushButtonDown.setText("")
        icon4 = QtGui.QIcon()
        icon4.addPixmap(QtGui.QPixmap(":/down.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButtonDown.setIcon(icon4)
        self.pushButtonDown.setIconSize(QtCore.QSize(48, 48))
        self.pushButtonDown.setObjectName("pushButtonDown")
        self.gridLayout.addWidget(self.pushButtonDown, 2, 1, 1, 1)
        self.verticalLayout.addLayout(self.gridLayout)

        self.retranslateUi(MoveDialog)
        self.comboBoxValue.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MoveDialog)

    def retranslateUi(self, MoveDialog):
        MoveDialog.setWindowTitle(QtGui.QApplication.translate("MoveDialog", "Перемещение", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBoxValue.setItemText(0, QtGui.QApplication.translate("MoveDialog", "1", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBoxValue.setItemText(1, QtGui.QApplication.translate("MoveDialog", "10", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBoxValue.setItemText(2, QtGui.QApplication.translate("MoveDialog", "100", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc

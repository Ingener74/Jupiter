# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'prebuild/res/main.ui'
#
# Created: Tue Aug 11 22:23:48 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_Main(object):
    def setupUi(self, Main):
        Main.setObjectName("Main")
        Main.resize(1306, 841)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/two_storied_house.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Main.setWindowIcon(icon)
        self.verticalLayout = QtGui.QVBoxLayout(Main)
        self.verticalLayout.setObjectName("verticalLayout")
        self.groupBox = QtGui.QGroupBox(Main)
        self.groupBox.setObjectName("groupBox")
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.groupBox)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.go = QtGui.QPushButton(self.groupBox)
        self.go.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/start.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.go.setIcon(icon1)
        self.go.setIconSize(QtCore.QSize(42, 42))
        self.go.setObjectName("go")
        self.horizontalLayout_2.addWidget(self.go)
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.verticalLayout.addWidget(self.groupBox)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.settingsGroupBox = QtGui.QGroupBox(Main)
        self.settingsGroupBox.setObjectName("settingsGroupBox")
        self.horizontalLayout.addWidget(self.settingsGroupBox)
        self.processGroupBox = QtGui.QGroupBox(Main)
        self.processGroupBox.setObjectName("processGroupBox")
        self.verticalLayout_3 = QtGui.QVBoxLayout(self.processGroupBox)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.listWidget = QtGui.QListWidget(self.processGroupBox)
        self.listWidget.setObjectName("listWidget")
        self.verticalLayout_3.addWidget(self.listWidget)
        self.horizontalLayout.addWidget(self.processGroupBox)
        self.horizontalLayout.setStretch(0, 1)
        self.horizontalLayout.setStretch(1, 1)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.logGroupBox = QtGui.QGroupBox(Main)
        self.logGroupBox.setObjectName("logGroupBox")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.logGroupBox)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.plainTextEdit = QtGui.QPlainTextEdit(self.logGroupBox)
        self.plainTextEdit.setReadOnly(True)
        self.plainTextEdit.setObjectName("plainTextEdit")
        self.verticalLayout_2.addWidget(self.plainTextEdit)
        self.verticalLayout.addWidget(self.logGroupBox)
        self.verticalLayout.setStretch(1, 4)
        self.verticalLayout.setStretch(2, 1)

        self.retranslateUi(Main)
        QtCore.QMetaObject.connectSlotsByName(Main)

    def retranslateUi(self, Main):
        Main.setWindowTitle(QtGui.QApplication.translate("Main", "Сборка зависимостей", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox.setTitle(QtGui.QApplication.translate("Main", "Управление", None, QtGui.QApplication.UnicodeUTF8))
        self.settingsGroupBox.setTitle(QtGui.QApplication.translate("Main", "Настройки сборки", None, QtGui.QApplication.UnicodeUTF8))
        self.processGroupBox.setTitle(QtGui.QApplication.translate("Main", "Процесс сборки компонентов", None, QtGui.QApplication.UnicodeUTF8))
        self.logGroupBox.setTitle(QtGui.QApplication.translate("Main", "Журнал событий", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc

# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:/Users/Pavel/workspace/Jupiter/apps/PyGameDesigner/res/GameDesignerAlt.ui'
#
# Created: Tue May 19 21:04:18 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_GameDesigner(object):
    def setupUi(self, GameDesigner):
        GameDesigner.setObjectName("GameDesigner")
        GameDesigner.resize(400, 792)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/qt_level_editor.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        GameDesigner.setWindowIcon(icon)
        self.verticalLayout_3 = QtGui.QVBoxLayout(GameDesigner)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.play = QtGui.QPushButton(GameDesigner)
        self.play.setObjectName("play")
        self.horizontalLayout.addWidget(self.play)
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout_3.addLayout(self.horizontalLayout)
        self.resourcesGroupBox = QtGui.QGroupBox(GameDesigner)
        self.resourcesGroupBox.setObjectName("resourcesGroupBox")
        self.verticalLayout = QtGui.QVBoxLayout(self.resourcesGroupBox)
        self.verticalLayout.setObjectName("verticalLayout")
        self.treeView_2 = QtGui.QTreeView(self.resourcesGroupBox)
        self.treeView_2.setObjectName("treeView_2")
        self.verticalLayout.addWidget(self.treeView_2)
        self.verticalLayout_3.addWidget(self.resourcesGroupBox)
        self.nodeTreeGroupBox = QtGui.QGroupBox(GameDesigner)
        self.nodeTreeGroupBox.setObjectName("nodeTreeGroupBox")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.nodeTreeGroupBox)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.treeView = QtGui.QTreeView(self.nodeTreeGroupBox)
        self.treeView.setObjectName("treeView")
        self.verticalLayout_2.addWidget(self.treeView)
        self.verticalLayout_3.addWidget(self.nodeTreeGroupBox)

        self.retranslateUi(GameDesigner)
        QtCore.QMetaObject.connectSlotsByName(GameDesigner)

    def retranslateUi(self, GameDesigner):
        GameDesigner.setWindowTitle(QtGui.QApplication.translate("GameDesigner", "Редактор игры", None, QtGui.QApplication.UnicodeUTF8))
        self.play.setText(QtGui.QApplication.translate("GameDesigner", "Запуск", None, QtGui.QApplication.UnicodeUTF8))
        self.resourcesGroupBox.setTitle(QtGui.QApplication.translate("GameDesigner", "Ресурсы", None, QtGui.QApplication.UnicodeUTF8))
        self.nodeTreeGroupBox.setTitle(QtGui.QApplication.translate("GameDesigner", "Дерево игры", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc

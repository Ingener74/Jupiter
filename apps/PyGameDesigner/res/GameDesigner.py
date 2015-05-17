# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:/Users/Pavel/workspace/Jupiter/apps/PyGameDesigner/res/GameDesigner.ui'
#
# Created: Sun May 17 21:08:53 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_GameDesigner(object):
    def setupUi(self, GameDesigner):
        GameDesigner.setObjectName("GameDesigner")
        GameDesigner.resize(1100, 795)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/qt_level_editor.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        GameDesigner.setWindowIcon(icon)
        self.verticalLayout_2 = QtGui.QVBoxLayout(GameDesigner)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.nodeTreeView = QtGui.QTreeView(GameDesigner)
        self.nodeTreeView.setObjectName("nodeTreeView")
        self.verticalLayout.addWidget(self.nodeTreeView)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.addNodeButton = QtGui.QPushButton(GameDesigner)
        self.addNodeButton.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/add.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.addNodeButton.setIcon(icon1)
        self.addNodeButton.setIconSize(QtCore.QSize(32, 32))
        self.addNodeButton.setObjectName("addNodeButton")
        self.horizontalLayout.addWidget(self.addNodeButton)
        self.removeNodeButton = QtGui.QPushButton(GameDesigner)
        self.removeNodeButton.setText("")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/rb_full.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.removeNodeButton.setIcon(icon2)
        self.removeNodeButton.setIconSize(QtCore.QSize(32, 32))
        self.removeNodeButton.setObjectName("removeNodeButton")
        self.horizontalLayout.addWidget(self.removeNodeButton)
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_2.addLayout(self.verticalLayout)
        self.widget = QtGui.QWidget(GameDesigner)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(1)
        sizePolicy.setHeightForWidth(self.widget.sizePolicy().hasHeightForWidth())
        self.widget.setSizePolicy(sizePolicy)
        self.widget.setMinimumSize(QtCore.QSize(0, 0))
        self.widget.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.widget.setObjectName("widget")
        self.verticalLayout_4 = QtGui.QVBoxLayout(self.widget)
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.glLayout = QtGui.QVBoxLayout()
        self.glLayout.setObjectName("glLayout")
        self.verticalLayout_4.addLayout(self.glLayout)
        self.horizontalLayout_2.addWidget(self.widget)
        self.verticalLayout_2.addLayout(self.horizontalLayout_2)

        self.retranslateUi(GameDesigner)
        QtCore.QMetaObject.connectSlotsByName(GameDesigner)

    def retranslateUi(self, GameDesigner):
        GameDesigner.setWindowTitle(QtGui.QApplication.translate("GameDesigner", "Редактор игр", None, QtGui.QApplication.UnicodeUTF8))

import resources_rc

#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import json
from PySide.QtGui import *
from PySide.QtOpenGL import *
from PySide.QtCore import *

from OpenGL.GL import *
from OpenGL.GLU import *

from res import *
from modules import *

COMPANY = 'Jupiter Organisation'
APPNAME = 'Europe Game Designer'


class NodeTreeModel(QAbstractItemModel):
    def __init__(self):
        QAbstractItemModel.__init__(self)
        
        self.__testMe = u'Попробуй'
        
        self.simpleList = [u'Паша', u'Какаша']
        
    def columnCount(self, parent):
        return 2
    
    def rowCount(self, parent):
        return len(self.simpleList)
        
    def index(self, row, column, parent):
        return self.createIndex(row, column, self.simpleList[row])
    
    def data(self, index, role=Qt.DisplayRole):
        if role == Qt.DisplayRole:
            if index.column() == 0:
                return index.internalPointer()
            if index.column() == 1:
                return "test"
            
        if role == Qt.EditRole:
            return "new"
    
    def parent(self, child):
        return QModelIndex()


class NodeSettings(QWidget, Ui_NodeSettings):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.restoreGeometry(self.settings.value(self.__class__.__name__))
        
    def closeEvent(self, e):
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.settings.setValue(self.__class__.__name__, self.saveGeometry())


class SpriteSettings(QWidget, Ui_SpriteSettings):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.restoreGeometry(self.settings.value(self.__class__.__name__))
        
    def closeEvent(self, e):
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.settings.setValue(self.__class__.__name__, self.saveGeometry())



class Box2dBodySettings(QWidget, Ui_Box2dBodySettings):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.restoreGeometry(self.settings.value(self.__class__.__name__))
        
    def closeEvent(self, e):
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.settings.setValue(self.__class__.__name__, self.saveGeometry())


class GlWidget(QGLWidget):
    
    WIDTH = 800
    HEIGHT = WIDTH * 3 / 5
    
    def __init__(self, parent=None):
        QGLWidget.__init__(self, parent, None)
        self.setObjectName(u'EuropeGLWidget')
        self.resize(self.WIDTH, self.HEIGHT)
        self.setWindowTitle(u'Европа, редактор игр Юпитера')
        self.setWindowIcon(QIcon(QPixmap(':/stationery.png')))
        
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.restoreGeometry(self.settings.value(self.__class__.__name__))
        
    def closeEvent(self, e):
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.settings.setValue(self.__class__.__name__, self.saveGeometry())
        
    def initializeGL(self):
        print 'Vendor   ', str(glGetString(GL_VENDOR))
        print 'Renderer ', str(glGetString(GL_RENDERER))
        print 'OpenGL   ', str(glGetString(GL_VERSION))
        print 'GLSL     ', str(glGetString(GL_SHADING_LANGUAGE_VERSION))
#         self.resize(800, 480) # try this
        
    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glClearColor(0.1, 0.3, 0.1, 1.0)
        
    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)


class GameDesignerWindow(QWidget, Ui_GameDesigner):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.restoreGeometry(self.settings.value(self.__class__.__name__))
        
        nodeTreeModel = NodeTreeModel()
        self.nodeTreeView.setModel(nodeTreeModel)
        self.nodeTreeView.setEditTriggers(QAbstractItemView.DoubleClicked)
        
        self.__base = QFileDialog.getExistingDirectory(caption=u'Директория с ресурсами', options=QFileDialog.ShowDirsOnly).encode('ascii', 'ignore')
        
        resourceModel = ResourceModel(self.__base)
        self.resourceTreeView.setModel(resourceModel)
        
        self.glWidget = GlWidget()
        self.glWidget.show()
        
        self.nodeSettings = NodeSettings()
        self.nodeSettings.show()
        
        self.spriteSettings = SpriteSettings()
        self.spriteSettings.show()
        
        self.box2dBodySettings = Box2dBodySettings()
        self.box2dBodySettings.show()
        
    def contextMenuEvent(self, e):
        menu = QMenu()
        menu.addAction(u'Посмотреть', self.showItem)
        menu.exec_(e.globalPos())
        
    def showItem(self):
        print 'Посмотреть'
    
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()
    
    def closeEvent(self, e):
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.settings.setValue(self.__class__.__name__, self.saveGeometry())

        self.glWidget.close()
        self.nodeSettings.close()
        self.spriteSettings.close()
        self.box2dBodySettings.close()


class Europe(QWidget, Ui_Europe):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)


def setStyle():
    if sys.platform == 'win32':
        QApplication.setStyle(u"windows")
    elif sys.platform == 'linux2':
        QApplication.setStyle(u"plastique")
    else:
        print u'Неизвестная система'

    
def main():
    import sys
    setStyle()
    app = QApplication(sys.argv)
    
    mainWindow = GameDesignerWindow()
    mainWindow.show()

    europe = Europe()
    europe.show()
    
    sys.exit(app.exec_())

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print 'Exception {}'.format(str(e))







#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import json
from PySide.QtGui import QWidget, QApplication, QMainWindow, QVBoxLayout, QMenu, QPushButton, QTreeView, QHBoxLayout
from PySide.QtOpenGL import QGLWidget
from PySide.QtCore import Qt, QPoint, QSettings, QAbstractItemModel, QModelIndex

from OpenGL.GL import *
from OpenGL.GLU import *

from res import *


COMPANY = 'Jupiter Organisation'
APPNAME = 'Europe Game Designer'


class NodeTreeModel(QAbstractItemModel):
    def __init__(self):
        QAbstractItemModel.__init__(self)
        
        self.simpleList = [u'Паша', u'Какаша']
        
    def columnCount(self, parent):
        return 1
    
    def rowCount(self, parent):
        return len(self.simpleList)
        
    def index(self, row, column, parent):
        return self.createIndex(row, column, 'data')
    
    def data(self, index, role=Qt.DisplayRole):
        row = index.row()
        return self.simpleList[row]
    
    def parent(self, child):
        return QModelIndex()


class NodeSettings(QWidget, Ui_NodeSettings):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        self.settings = None
        
    def closeEvent(self, e):
        # Альтернативный способ сохранения геометрии окна
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.settings.setValue('geometry', self.saveGeometry())
        print self.settings.fileName()
        QWidget.closeEvent(self, e)


class SpriteSettings(QWidget, Ui_SpriteSettings):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)


class Box2dBodySettings(QWidget, Ui_Box2dBodySettings):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)


class GlWidget(QGLWidget):
    
    WIDTH = 800
    HEIGHT = WIDTH * 3 / 5
    
    def __init__(self, parent=None):
        QGLWidget.__init__(self, parent, None)
        self.setObjectName(u'EuropeGLWidget')
        self.resize(self.WIDTH, self.HEIGHT)
        self.setWindowTitle(u'Европа, редактор игр Юпитера')
        
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
    
    CONFIG_NAME = 'config.json'
    
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)
        
        
        nodeTreeModel = NodeTreeModel()
        self.nodeTreeView.setModel(nodeTreeModel)
        
        
        self._json = json.load(open(self.CONFIG_NAME))
        
        self.move(self.loadWidgetPosition(self))
        
        self.glWidget = GlWidget()
        self.glWidget.move(self.loadWidgetPosition(self.glWidget))
        self.glWidget.show()
        
        self.nodeSettings = NodeSettings()
        self.nodeSettings.move(self.loadWidgetPosition(self.nodeSettings))
        self.nodeSettings.show()
        
        self.spriteSettings = SpriteSettings()
        self.spriteSettings.move(self.loadWidgetPosition(self.spriteSettings))
        self.spriteSettings.show()
        
        self.box2dBodySettings = Box2dBodySettings()
        self.box2dBodySettings.move(self.loadWidgetPosition(self.box2dBodySettings))
        self.box2dBodySettings.show()
        
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()
    
    def closeEvent(self, e):
        self.saveWidgetPosition(self)
        
        self.saveWidgetPosition(self.glWidget)
        self.glWidget.close()
        
        self.saveWidgetPosition(self.nodeSettings)
        self.nodeSettings.close()
        
        self.saveWidgetPosition(self.spriteSettings)
        self.spriteSettings.close()
        
        self.saveWidgetPosition(self.box2dBodySettings)
        self.box2dBodySettings.close()
        
    def loadWidgetPosition(self, widget):
        return QPoint(self._json[widget.objectName()]['x'], self._json[widget.objectName()]['y'])
    
    def saveWidgetPosition(self, window):
        self._json[window.objectName().encode('ascii', 'ignore')]['x'] = window.x()
        self._json[window.objectName().encode('ascii', 'ignore')]['y'] = window.y()
        with open(self.CONFIG_NAME, 'w') as file:
            json.dump(self._json, file, indent=4, separators=(',', ':'), sort_keys=True)


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
    
    sys.exit(app.exec_())

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print 'Exception {}'.format(str(e))







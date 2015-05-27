#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
from PySide.QtGui import *
from PySide.QtCore import *

class ListModel(QAbstractListModel):
    def __init__(self):
        QAbstractListModel.__init__(self)
        self.__data = ['Item1', 'Item2']
    
    def rowCount(self, parent):
        return len(self.__data)
    
    def data(self, index, role = Qt.DisplayRole):
        if role == Qt.DisplayRole:
            return self.__data[index.row()]
        else:
            return None
    
    def flags(self, index):
        return Qt.ItemIsEnabled | Qt.ItemIsEditable
    
    def setData(self, index, value, role):
        if index.isValid():
            self.__data[index.row()] = value
            self.dataChanged.emit(index, index)
            return True
        else:
            return False
    
    def addItem(self, data):
        self.__data.append(data)
        self.dataChanged.emit(QModelIndex(), QModelIndex())

class ListView(QWidget):
    COMPANY = 'Venus'
    APPNAME = 'Dawn'
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        
        self.model = ListModel()
        
        add = QPushButton(u'Добавить')
        add.clicked.connect(self.addClick)
        listView = QListView()
        listView.setModel(self.model)
        listView.clicked.connect(self.onClicked)
        
        combo = QComboBox()
        combo.setModel(self.model)
        
        ver = QVBoxLayout()
        ver.addWidget(listView)
        ver.addWidget(combo)
        ver.addWidget(add)
        
        self.setLayout(ver)
        
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, self.COMPANY, self.APPNAME)
        self.restoreGeometry(self.settings.value('listView'))
        
    def addClick(self):
        self.model.addItem('newItem')
        
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()
    
    def closeEvent(self, e):
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, self.COMPANY, self.APPNAME)
        self.settings.setValue('listView', self.saveGeometry())
        QWidget.closeEvent(self, e)
        
    def onClicked(self, index):
        print index

def setStyle():
    if sys.platform == 'win32':
        QApplication.setStyle(u"windows")
    elif sys.platform == 'linux2':
        QApplication.setStyle(u"plastique")
    else:
        print u'Неизвестная система'

if __name__ == '__main__':
    setStyle()
    app = QApplication(sys.argv)
    
    listView = ListView()
    listView.show()
    
    sys.exit(app.exec_())



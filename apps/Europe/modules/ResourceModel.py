# encoding: utf-8

import os
import string

from PySide.QtCore import Qt, QAbstractItemModel, QModelIndex

from JupiterPython import *

"""

Types = {"Image", "Texture", "Shape", "Shader", ... }

{
    "Resource": {
        "Type": "Image",
        "Object": <object>,
        "Childrens": {
            "Resource":{
                "Type": "Texture"
                "Object": <object>
            },
            "Resource":{
                "Type": "Shape"
                "Object": <object>
            }
        }
    }
}

"""


class Resource(object):

    NONE = "None"
    IMAGE = "PngImage"
    TEXTURE = "ImageTexture"
    SHAPE = "ImageShape"
    SHADER = "Shader"
    
    def __init__(self, type_=NONE, name="Noname", obj=None):
        self.__type = type_
        self.__name = name
        self.__parent = None
        self.__childs = []
        self.__object = obj

    def addChild(self, child):
        child.setParent(self)
        self.__childs.append(child)
        
    def child(self, indx):
        return self.__childs[indx]
    
    def childCount(self):
        return len(self.__childs)
    
    def getName(self):
        return self.__name
    
    def getType(self):
        return self.__type
    
    def setParent(self, parent):
        self.__parent = parent
        
    def getParent(self):
        return self.__parent
    
    def index(self, child):
        return self.__childs.index(child)
    
    def getObject(self):
        return self.__object
        
    def __str__(self):
        return self.__type + ': ' + self.__name
    
    def __repr__(self):
        return str(self)


class ResourceModel(QAbstractItemModel):
    def __init__(self, base):
        QAbstractItemModel.__init__(self)
        
        self.base = base
        File.setBase(self.base)
        
        self.__root = Resource()
        
        self.refresh()
        
    def rowCount(self, parent):
        if not parent.isValid():
            return self.__root.childCount()
        else:
            return parent.internalPointer().childCount()
        
    def columnCount(self, parent):
        return 4
    
    def data(self, index, role):
        if role == Qt.DisplayRole:
            
            R = index.internalPointer()
            
            if index.column() == 0:
                return R.getName()
            elif index.column() == 1:
                return R.getType()
            elif index.column() == 2:
                if R.getType() == Resource.IMAGE:
                    return R.getObject().getWidth()
                else:
                    return ''
            elif index.column() == 3:
                if R.getType() == Resource.IMAGE:
                    return R.getObject().getHeight()
                else:
                    return ''
        return None
    
    def headerData(self, section, orientation, role):
        if role == Qt.DisplayRole:
            if orientation == Qt.Horizontal:
                if section == 0:
                    return 'Name'
                if section == 1:
                    return 'Type'
                if section == 2:
                    return 'Width'
                if section == 3:
                    return 'Height'
            if orientation == Qt.Vertical:
                return str(section)
        return None
    
    def index(self, row, column, parent):
        if not parent.isValid():
            parentRes = self.__root
        else:
            parentRes = parent.internalPointer()
        
        child = parentRes.child(row)
        
        if child:
            return self.createIndex(row, column, child)
        else:
            return QModelIndex()
        
    def parent(self, child):
        if not child.isValid():
            return QModelIndex()
        
        childRes = child.internalPointer()
        parent = childRes.getParent()
        
        if parent == self.__root:
            return QModelIndex()
        else:
            return self.createIndex(parent.index(childRes), 0, parent)
        
    def refresh(self):
        for dirname, dirnames, fileanames in os.walk(self.base):
            resDir = os.path.relpath(dirname, self.base)
            for filen in fileanames:
                filenFull, filenExt = os.path.splitext(filen)
                if filenExt == '.png':
                    path_ = resDir + '/' + filen
                    self.addPngImage(path_.translate(string.maketrans('\\', '/')))
    
    def addPngImage(self, pngImage):
        jimage = PngImage(pngImage)
        image = Resource(Resource.IMAGE, pngImage, jimage)
        
        jtex = ImageTexture(jimage)
        imageTexture = Resource(Resource.TEXTURE, pngImage, jimage)
        image.addChild(imageTexture)
        
        jshape = ImageShape(jimage)
        imageShape = Resource(Resource.SHAPE, pngImage, jshape)
        image.addChild(imageShape)
        
        self.__root.addChild(image)
        
    def addShader(self, vs, fs):
        pass
        

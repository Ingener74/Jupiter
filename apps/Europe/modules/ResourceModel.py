# encoding: utf-8

from PySide.QtCore import Qt, QAbstractItemModel, QModelIndex
import os
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
    
    NONE        = "None"
    IMAGE       = "PngImage"
    TEXTURE     = "ImageTexture"
    SHAPE       = "ImageShape"
    SHADER      = "Shader"
    
    def __init__(self, type_=NONE, name="Noname", obj=None, parent=None):
        self.__type     = type_
        self.__name     = name
        self.__object   = obj
        self.__parent   = parent
        self.__childs   = []

    def addChild(self, type, name, obj, parent):
        self.__childs.append(Resource(type, name, obj, parent))
    def child(self, index):
        return __childs[index]
    def childCount(self):
        return len(self.__data)
    def getName(self):
        return __name
    def getType(self):
        return __type
        
    def __str__(self):
        return self.__type + ': ' + self.__name
    def __repr__(self):
        return str(self)

class ResourceModel(QAbstractItemModel):
    def __init__(self, base):
        QAbstractItemModel.__init__(self)
        
        self.base = base
        
        #File.setBase(self.base)
        
        self.__data = []
        
        r1 = Resource(Resource.IMAGE, 'Image1')
        t1 = Resource(Resource.TEXTURE, 'Texture1', None, r1)
        
        r2 = Resource(Resource.IMAGE, 'Image2')
        t2 = Resource(Resource.TEXTURE, 'Texture2', None, r2)
        
        self.__data.append(r1)
        self.__data.append(r2)
        
        #self.refresh()
        
        for i in self.__data:
            print i
        
    def rowCount(self, parent):
        print 'rowCount', parent
        if not parent.isValid():
            return len(self.__data)
        else:
            return len(parent.internalPointer().childCount())
        
    def columnCount(self, parent):
        print 'columnCount', parent
        return 2
    
    def data(self, index, role):
        print 'data', index, role
        if role == Qt.DisplayRole:
            if index.column == 0:
                return index.internalPointer().getName()
            else:
                return index.internalPointer().getType()
        return None
    
    def headerData(self, section, orientation, role):
        if role == Qt.DisplayRole:
            if orientation == Qt.Horizontal:
                if section == 0:
                    return 'Name'
                if section == 1:
                    return 'Type'
            if orientation == Qt.Vertical:
                return str(section)
        return None
    
    def index(self, row, column, parent):
        print 'index', row, column, parent
        if not self.hasIndex(row, column, parent):
            return QModelIndex()
        
        if not parent.isValid():
            return QModelIndex()
        else:
            return self.createIndex(row, column, parent.internalPointer().child(row))
        
        return self.createIndex(row, column, self.__data[row])
        
    def parent(self, child):
        print 'parent', child
        
    def refresh(self):
        for dirname, dirnames, fileanames in os.walk(self.base):
            resDir = os.path.relpath(dirname, self.base)
            for filen in fileanames:
                filenFull, filenExt = os.path.splitext(filen)
                if filenExt == '.png':
                    self.addPngImage(resDir + '/' + filen)
    
    def addPngImage(self, pngImage):
        print pngImage
        
        #Jupiter PngImage
        jimage = PngImage(pngImage)
        
        image = Resource(Resource.IMAGE, pngImage, jimage)
        self.__data.append(image)
        
        # Jupiter Texture
        jtex = ImageTexture(jimage)
        imageTexture = Resource(Resource.TEXTURE, pngImage, jimage, image)
        
        # Jupiter Shape
        jshape = ImageShape(jimage)
        imageShape = Resource(Resource.SHAPE, pngImage, jshape, image)
        
    def addShader(self, vs, fs):
        pass
        

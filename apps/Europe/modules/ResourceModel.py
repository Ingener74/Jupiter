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
    
    def __init__(self, type_=NONE, name="Noname", parent=None, obj=None):
        self.__type     = type_
        self.__name     = name
        self.__parent   = parent
        self.__childs   = []
        self.__object   = obj

    def addChild(self, type, name, obj, parent):
        self.__childs.append(Resource(type, name, obj, parent))
    def child(self, index):
        return self.__childs[index]
    def childCount(self):
        return len(self.__childs)
    def getName(self):
        return self.__name
    def getType(self):
        return self.__type
    def getParent(self):
        return self.__parent
        
    def __str__(self):
        return self.__type + ': ' + self.__name
    def __repr__(self):
        return str(self)

class ResourceModel(QAbstractItemModel):
    def __init__(self, base):
        QAbstractItemModel.__init__(self)
        
        self.base = base
        
        File.setBase(self.base)
        
        self.__data = []
        
        root = Resource()
        
        r1 = Resource(Resource.IMAGE,   'Image1',   root)
        t1 = Resource(Resource.TEXTURE, 'Texture1', r1)
        s1 = Resource(Resource.SHAPE,   'Shape1',   r1)
        
        r2 = Resource(Resource.IMAGE,   'Image2',   root)
        t2 = Resource(Resource.TEXTURE, 'Texture2', r2)
        s2 = Resource(Resource.SHAPE,   'Shape2',   r2)
        
        self.__data.append(root)
        
        #self.refresh()
        
        for i in self.__data:
            print i
        
    def rowCount(self, parent):
        if not parent.isValid():
            return len(self.__data)
        else:
            res = parent.internalPointer()
            return res.childCount()
        
    def columnCount(self, parent):
        return 2
    
    def data(self, index, role):
        if role == Qt.DisplayRole:
            if index.column() == 0:
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
        if not parent.isValid():
            parentRes = self.__data[row]
        else:
            parentRes = parent.internalPointer()
        
        return self.createIndex(row, column, parentRes)
        
    def parent(self, child):
        childRes = child.internalPointer()
        if childRes.getParent() == None:
            return QModelIndex()
        else:
            return
        
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
        

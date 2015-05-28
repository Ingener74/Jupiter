# encoding: utf-8

from PySide.QtCore import Qt, QAbstractItemModel, QModelIndex
import os

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


class ResourceModel(QAbstractItemModel):
    def __init__(self, base):
        QAbstractItemModel.__init__(self)
        
        self.base = base
        
        self.__data = []
        
        self.refresh()
        
    def rowCount(self, parent=QModelIndex()):
        return len(self.__data)
        
    def columnCount(self, parent=QModelIndex()):
        return 1
    
    def data(self, index, role=Qt.DisplayRole):
        if role == Qt.DisplayRole:
            return self.__data[index.row()]
        return None
        
    def index(self, row, column, parent=QModelIndex()):
        return QModelIndex()
        
    def refresh(self):
        for dirname, dirnames, fileanames in os.walk(self.base):
            resDir = os.path.relpath(dirname, self.base)
            for filen in fileanames:
                filenFull, filenExt = os.path.splitext(filen)
                if filenExt == '.png':
                    print 
                    self.addPngImage(resDir + '/' + filen)
    
    def addPngImage(self, pngImage):
        
        #Jupiter PngImage
        
        image = Resource(Resource.IMAGE, pngImage, ... )
        self.__data.append(image)
        
        # Jupiter Texture
        
        imageTexture = Resource(Resource.TEXTURE, pngImage, ... , image)
        
        # Jupiter Shape
        
        imageShape = Resource(Resource.SHAPE, pngImage, ... , image)
        
    def addShader(self, vs, fs):
        pass
        

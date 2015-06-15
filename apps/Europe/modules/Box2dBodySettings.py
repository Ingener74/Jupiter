from PySide.QtCore import QSettings
from PySide.QtGui import QWidget
from Europe import COMPANY, APPNAME
from res import Ui_Box2dBodySettings

class Box2dBodySettings(QWidget, Ui_Box2dBodySettings):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setupUi(self)

        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.restoreGeometry(self.settings.value(self.__class__.__name__))

    def closeEvent(self, e):
        self.settings = QSettings(QSettings.IniFormat, QSettings.UserScope, COMPANY, APPNAME)
        self.settings.setValue(self.__class__.__name__, self.saveGeometry())
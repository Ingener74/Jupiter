from PySide.QtGui import QApplication, QWidget, QPixmap, QBrush, QPainter
import sys

class PainterWidget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)

        self.pixmap = QPixmap('../../samples/Box/Resources/Lollipop.png')

    def paintEvent(self, e):

        painter = QPainter()

        painter.begin(self)
        painter.drawPixmap(0, 0, 400, 400 * float(self.pixmap.height()) / float(self.pixmap.width()), self.pixmap)
        painter.end()

if __name__ == '__main__':
    app = QApplication(sys.argv)

    paint = PainterWidget()
    paint.show()

    sys.exit(app.exec_())
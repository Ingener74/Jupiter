#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

from PySide.QtGui import (QApplication)

from Io import Select

if __name__ == '__main__':
    try:
        # noinspection PyCallByClass,PyTypeChecker
        QApplication.setStyle(u'plastique')
        app = QApplication(sys.argv)

        select = Select()
        select.show()

        sys.exit(app.exec_())
    except RuntimeError, e:
        print str(e)

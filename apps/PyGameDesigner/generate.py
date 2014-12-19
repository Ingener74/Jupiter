#!/usr/bin/env python
# -*- coding: utf-8 -*-

import subprocess

subprocess.Popen(['pyside-rcc', 'res/GameDesigner.qrc', '-o', 'GameDesigner_rc.py'])

subprocess.Popen(['pyside-uic', 'ui/main.ui', '-o', 'main_editor_window.py'])

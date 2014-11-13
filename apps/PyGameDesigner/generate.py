#!/usr/bin/env python
# -*- coding: utf-8 -*-

import subprocess

subprocess.Popen(['pyside-rcc', '../GameDesigner/res/GameDesigner.qrc', '-o', 'GameDesigner_rc.py'])

subprocess.Popen(['pyside-uic', '../GameDesigner/ui/main.ui', '-o', 'main_editor_window.py'])

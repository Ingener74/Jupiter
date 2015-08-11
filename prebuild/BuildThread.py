# encoding: utf8
import sys

from PySide.QtCore import QThread, QProcess, QProcessEnvironment


class BuildThread(QThread):
    def __init__(self):
        QThread.__init__(self)

        self.proc = None

    def on_read_stdout(self):
        if self.proc:
            # out = str(self.proc.readAllStandardOutput())
            # sys.stdout.write(out)
            sys.stdout.write(self.proc.readAllStandardOutput())

    def on_read_error(self):
        if self.proc:
            # err = str(self.proc.readAllStandardError())
            # sys.stderr.write(err)
            sys.stderr.write(self.proc.readAllStandardError())

    def finished_bash(self, exit_code):
        print exit_code

    def run(self, *args, **kwargs):

        build_directory = 'build_directory'

        # Windows
        bash_exe = 'C:/MinGW/msys/1.0/bin/bash.exe'

        # Linux
        # bash_exe = 'bash'

        box2d_tarball = 'https://github.com/erincatto/Box2D/archive/master.zip'
        box2d_github = 'https://github.com/erincatto/Box2D.git'
        box2d_branch = 'v2.3.1'

        packages = []

        for p in packages:
            print 'build package'

        env = QProcessEnvironment.systemEnvironment()
        env.insert('PATH', env.value('Path') + ';C:\\MinGW\\bin;'
                                               'C:\\MinGW\\mingw32\\bin;'
                                               'C:\\MinGW\\msys\\1.0\\bin;'
                                               'C:\\cygwin64\\bin;'
                                               'C:\\Program Files (x86)\\Git\\bin;'
                                               'C:\\Program Files (x86)\\CMake\\bin')

        # bash.start('bash')

        bash = QProcess()
        self.proc = bash
        bash.setProcessEnvironment(env)
        bash.readyReadStandardOutput.connect(self.on_read_stdout)
        bash.readyReadStandardError.connect(self.on_read_error)
        bash.finished.connect(self.finished_bash)
        bash.start(bash_exe)

        if bash.waitForStarted():
            # bash.write('rm -rf ' + build_directory +
            #            ' && mkdir -p ' + build_directory +
            #            ' && cd ' + build_directory +
            #            ' && wget ' + box2d_tarball +
            #            ' && ')

            bash.write('rm -rf ' + build_directory +
                       ' && mkdir -p ' + build_directory +
                       ' && cd ' + build_directory +
                       ' && git clone ' + box2d_github +
                       ' && mkdir -p Box2D/Box2D/build_win ' +
                       ' && cd Box2D/Box2D/build_win ' +
                       ' && echo cd_build ' +
                       ' && cmake .. -G \"MSYS Makefiles\"' +
                       ' && echo cmake++ ' +
                       ' && cmake --build . ' +
                       ' && echo cmake_build ')
            bash.closeWriteChannel()
            bash.waitForReadyRead()

        print 'Build thread finished'

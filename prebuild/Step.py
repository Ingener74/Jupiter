# encoding: utf8
from PySide.QtCore import QProcess


class Step(object):
    def __init__(self, command, env=None):
        self.text_edit = None
        self.output = None

        proc = QProcess()
        proc.readyReadStandardOutput.connect(self.on_read_stdout)
        proc.readyReadStandardError.connect(self.on_read_stdout)
        proc.finished.connect(self.finished)

        if env:
            proc.setProcessEnvironment(env)

        proc.start('bash')

        if not proc.waitForStarted():
            print 'wait for started'
            return

        # print bash.write('cd build-win && ls && make')
        proc.write(command)
        proc.waitForBytesWritten()

        # if not bash.waitForFinished():
        #     print 'wait for finished'
        #     return False
        # print bash.readAll()

    def run(self):
        pass

    def on_read_stdout(self):
        if self.text_edit:
            self.text_edit.append(str(self.proc.readAllStandardOutput()))
            self.text_edit.append(str(self.proc.readAllStandardError()))

    def set_output(self, output):
        self.output = output

    def finished(self, exit_code):
        print exit_code

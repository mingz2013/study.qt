#!/usr/bin/python

# absolute.py

import sys
from PyQt4 import QtGui

class Absolute(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        
        self.setWindowTitle('Communication')
        
        label = QtGui.QLabel('Could\'t', self)
        label.move(15, 10)

        label = QtGui.QLabel('care', self)
        label.move(35, 40)

        label = QtGui.QLabel('less', self)
        label.move(55, 65)

        label = QtGui.QLabel('And', self)
        label.move(115, 65)

        label = QtGui.QLabel('then', self)
        label.move(135, 45)

        label = QtGui.QLabel('you', self)
        label.move(115, 25)

        label = QtGui.QLabel('kissed', self)
        label.move(145, 10)

        label = QtGui.QLabel('me', self)
        label.move(215, 10)

        self.resize(250, 150)

app = QtGui.QApplication(sys.argv)
qb = Absolute()
qb.show()
sys.exit(app.exec_())
#!/usr/bin/python

# toolbar.py

import sys
from PyQt4 import QtGui, QtCore
 
class MainWindow(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        
        self.resize(250, 150)
        self.setWindowTitle('toolbar')
        
        self.exit = QtGui.QAction(QtGui.QIcon('icons/web.png'), 'Exit', self)
        self.exit.setShortcut('Ctrl+Q')
        self.connect(self.exit, QtCore.SIGNAL('triggered()'), QtCore.SLOT('close()'))

        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(self.exit)

app = QtGui.QApplication(sys.argv)
main = MainWindow()
main.show()
sys.exit(app.exec_())
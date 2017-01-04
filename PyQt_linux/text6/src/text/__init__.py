#!/usr/bin/python

# messagebox.py

import sys
from PyQt4 import QtGui

class MessageBox(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)

        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('message box')

    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message', 'Are you sure to quit?', QtGui.QMessageBox.Yes, QtGui.QMessageBox.No)
        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()
            
        
app = QtGui.QApplication(sys.argv)
mb = MessageBox()
mb.show()
sys.exit(app.exec_())
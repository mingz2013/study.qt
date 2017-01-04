import sys
from PyQt4.QtGui import *
from PyQt4.QtCore import *
 
app = QApplication(sys.argv)
label = QLabel("<font color=red size=128><b>Hello PyQT!</b></font>")
label.setWindowFlags(Qt.SplashScreen)
label.show()
QTimer.singleShot(10000, app.quit) 
app.exec_()
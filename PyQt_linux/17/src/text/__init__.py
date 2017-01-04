import sys
from PyQt4.QtGui import *
from PyQt4.QtCore import *
 
msg = "Hello PyQt!"
app = QApplication(sys.argv)
font = QFont("Times New Rome", 36, QFont.Bold)
fm = QFontMetrics(font)
pixmap = QPixmap(fm.width(msg) + 5, fm.height() + 5)
pixmap.fill(Qt.white)
painter = QPainter(pixmap)
document = QTextDocument()
document.setDefaultFont(font)
document.setHtml("<font color=red>%s</font>" % msg)
document.drawContents(painter)
label = QLabel()
label.setPixmap(pixmap)
label.setMask(pixmap.createMaskFromColor(Qt.red))
#label.setWindowFlags(Qt.SplashScreen|Qt.FramelessWindowHint)
label.show()
QTimer.singleShot(10000, app.quit) # 1 minute
app.exec_()
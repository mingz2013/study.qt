# coding=utf-8
#!/usr/bin/python

# simple.py
 
import sys
from PyQt4 import QtGui
                            # 这里，我们导入了必要的模块，PyQt4的基本模块都在QtGui中。
 
                               
app = QtGui.QApplication(sys.argv)
                            # 每一个PyQt4程序都必须创建一个application对象，application类位于QtGui模块中。
                            # sys.argv传入命令行参数。Python脚本可以通过shell运行，这样我们就可以对程序的启动进行控制。
 
widget = QtGui.QWidget()
                            # QWidget是PyQt4中所有用户接口对象的基类，我们使用QWidget默认的构造方法来创建QWidget对象，
                            # 默认的构造方法没有指定父控件，如果一个widget没有指定父控件，那么我们就称他为一个window。
                            
widget.resize(250, 150)     # resize()方法调整widget的大小，在这里我们设定宽度为250px，高度为150px。

widget.setWindowTitle('simple')#  setWindowTitle()方法设置了窗口的title，title在titlebar中显示。
widget.show()               # 调用show()方法将窗口显示出来。

sys.exit(app.exec_())
                            #    最后，就会进入application的事件循环。事件处理就从这里开始，
                            # 循环不断的从窗口接受需要处理的事件，然后将其分发给相应的时间处理方法。
                            # 通过调用exit()方法或者销毁widget来终止事件循环，调用sys.exit()方法确保了程序可以明确的退出，
                            # 也就是程序退出后会告知系统。
                            # 也许你会问，为什么exec_()方法最后会有一个下划线？问得非常好，这完全是因为exec是python的一个关键字
                            # ，所以我们不得不使用exec_来代替。

# -*- coding: utf-8 -*-
import sys
from time import time
from PyQt4.QtCore import *

class A (QObject):
    def __init__(self):
        QObject.__init__(self)
   
    #定义一个发射信号的方法，i为信号所带的参数
    def afunc (self, i):
        self.emit(SIGNAL("doSomePrinting(int)"), i)    
   
    #这里是对应信号'doSomePrinting(int)'的槽处理函数，i为来自信号的参数
    def bfunc(self, i):
        print "Hello World!", i
        sys.exit()

if __name__=="__main__":
    app=QCoreApplication(sys.argv)
    a=A()
    #将信号和槽连接
    QObject.connect(a,SIGNAL("doSomePrinting(int)"),a.bfunc)
    #调用信号发射函数
    a.afunc(10)    
    sys.exit(app.exec_())
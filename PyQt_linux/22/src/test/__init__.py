# -*- coding: utf-8 -*-

import sys

from PyQt4 import QtCore, QtGui
#从模块导入类
from ui_notepad import Ui_notepad

class StartQt4(QtGui.QMainWindow):
    
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_notepad()
        self.ui.setupUi(self)
        self.filename = None
        # 链接槽函数
        QtCore.QObject.connect(self.ui.button_open,QtCore.SIGNAL("clicked()"), self.file_dialog)
        QtCore.QObject.connect(self.ui.button_save,QtCore.SIGNAL("clicked()"), self.file_save)
        QtCore.QObject.connect(self.ui.editor_window,QtCore.SIGNAL("textChanged()"), self.enable_save)
    # 槽函数
    def file_dialog(self):
        response = False
        # buttons texts
        SAVE = 'Save'
        DISCARD = 'Discard'
        CANCEL = 'Cancel'
        # if we have changes then ask about them
        if self.ui.button_save.isEnabled() and self.filename:
            message = QtGui.QMessageBox(self)
            message.setText('What to do about unsaved changes ?')
            message.setWindowTitle('Notepad')
            message.setIcon(QtGui.QMessageBox.Question)
            message.addButton(SAVE, QtGui.QMessageBox.AcceptRole)
            message.addButton(DISCARD,QtGui.QMessageBox.DestructiveRole)
            message.addButton(CANCEL, QtGui.QMessageBox.RejectRole)
            message.setDetailedText('Unsaved changes in file: ' +str(self.filename))
            message.exec_()
            response = message.clickedButton().text()
            # save file
            if response == SAVE:
                self.file_save()
                self.ui.button_save.setEnabled(False)
                # discard changes
            elif response == DISCARD:
                self.ui.button_save.setEnabled(False)
                # if we didn't cancelled show the file dialogue
        if response != CANCEL:
            #启动 打开文件对话框，返回一个句柄
            fd = QtGui.QFileDialog(self)
            # 得到文件名
            self.filename = fd.getOpenFileName()
            # 导入
            from os.path import isfile
            # 判断是否是个文件
            if isfile(self.filename):
                import codecs
                # 支持utf8打开文件 并读取内容
                s = codecs.open(self.filename,'r','utf-8').read()
                # 显示文本
                self.ui.editor_window.setPlainText(s)
                # 设置保存按钮可见性
                self.ui.button_save.setEnabled(False)
            
    def file_save(self):
        from os.path import isfile
        if isfile(self.filename):
            import codecs
            s = codecs.open(self.filename,'w','utf-8')
            s.write(unicode(self.ui.editor_window.toPlainText()))
            s.close()
            self.ui.button_save.setEnabled(False)
            
    def enable_save(self):
        # 设置 保存按钮 可见
        self.ui.button_save.setEnabled(True)

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myapp = StartQt4()
    myapp.show()
    sys.exit(app.exec_())
# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'findandreplacedlg.ui'
#
# Created: Wed Jul 10 11:21:24 2013
#      by: PyQt4 UI code generator 4.10
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_FindAndReplaceDlg(object):
    def setupUi(self, FindAndReplaceDlg):
        FindAndReplaceDlg.setObjectName(_fromUtf8("FindAndReplaceDlg"))
        FindAndReplaceDlg.resize(400, 300)
        self.line = QtGui.QFrame(FindAndReplaceDlg)
        self.line.setGeometry(QtCore.QRect(260, 30, 20, 251))
        self.line.setFrameShape(QtGui.QFrame.VLine)
        self.line.setFrameShadow(QtGui.QFrame.Sunken)
        self.line.setObjectName(_fromUtf8("line"))
        self.widget = QtGui.QWidget(FindAndReplaceDlg)
        self.widget.setGeometry(QtCore.QRect(10, 20, 253, 261))
        self.widget.setObjectName(_fromUtf8("widget"))
        self.verticalLayout = QtGui.QVBoxLayout(self.widget)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.label = QtGui.QLabel(self.widget)
        self.label.setObjectName(_fromUtf8("label"))
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.findLineEdit = QtGui.QLineEdit(self.widget)
        self.findLineEdit.setObjectName(_fromUtf8("findLineEdit"))
        self.gridLayout.addWidget(self.findLineEdit, 0, 1, 1, 1)
        self.label_2 = QtGui.QLabel(self.widget)
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.replaceLineEdit = QtGui.QLineEdit(self.widget)
        self.replaceLineEdit.setObjectName(_fromUtf8("replaceLineEdit"))
        self.gridLayout.addWidget(self.replaceLineEdit, 1, 1, 1, 1)
        self.verticalLayout.addLayout(self.gridLayout)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.caseCheckBox = QtGui.QCheckBox(self.widget)
        self.caseCheckBox.setObjectName(_fromUtf8("caseCheckBox"))
        self.horizontalLayout.addWidget(self.caseCheckBox)
        self.wholCheckBox = QtGui.QCheckBox(self.widget)
        self.wholCheckBox.setChecked(True)
        self.wholCheckBox.setObjectName(_fromUtf8("wholCheckBox"))
        self.horizontalLayout.addWidget(self.wholCheckBox)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.label_3 = QtGui.QLabel(self.widget)
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.horizontalLayout_2.addWidget(self.label_3)
        self.syntaxComboBox = QtGui.QComboBox(self.widget)
        self.syntaxComboBox.setObjectName(_fromUtf8("syntaxComboBox"))
        self.syntaxComboBox.addItem(_fromUtf8(""))
        self.syntaxComboBox.addItem(_fromUtf8(""))
        self.horizontalLayout_2.addWidget(self.syntaxComboBox)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        spacerItem = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem)
        self.widget1 = QtGui.QWidget(FindAndReplaceDlg)
        self.widget1.setGeometry(QtCore.QRect(280, 23, 95, 261))
        self.widget1.setObjectName(_fromUtf8("widget1"))
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.widget1)
        self.verticalLayout_2.setMargin(0)
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.findButton = QtGui.QPushButton(self.widget1)
        self.findButton.setObjectName(_fromUtf8("findButton"))
        self.verticalLayout_2.addWidget(self.findButton)
        self.replaceButton = QtGui.QPushButton(self.widget1)
        self.replaceButton.setObjectName(_fromUtf8("replaceButton"))
        self.verticalLayout_2.addWidget(self.replaceButton)
        self.replaceAllButton = QtGui.QPushButton(self.widget1)
        self.replaceAllButton.setObjectName(_fromUtf8("replaceAllButton"))
        self.verticalLayout_2.addWidget(self.replaceAllButton)
        spacerItem1 = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout_2.addItem(spacerItem1)
        self.closeButton = QtGui.QPushButton(self.widget1)
        self.closeButton.setObjectName(_fromUtf8("closeButton"))
        self.verticalLayout_2.addWidget(self.closeButton)
        self.label.setBuddy(self.findLineEdit)
        self.label_2.setBuddy(self.replaceLineEdit)
        self.label_3.setBuddy(self.syntaxComboBox)

        self.retranslateUi(FindAndReplaceDlg)
        QtCore.QObject.connect(self.closeButton, QtCore.SIGNAL(_fromUtf8("clicked()")), FindAndReplaceDlg.reject)
        QtCore.QMetaObject.connectSlotsByName(FindAndReplaceDlg)

    def retranslateUi(self, FindAndReplaceDlg):
        FindAndReplaceDlg.setWindowTitle(_translate("FindAndReplaceDlg", "Find and Replace", None))
        self.label.setText(_translate("FindAndReplaceDlg", "Find &what", None))
        self.label_2.setText(_translate("FindAndReplaceDlg", "Replace with", None))
        self.caseCheckBox.setText(_translate("FindAndReplaceDlg", "&Case sensitive", None))
        self.wholCheckBox.setText(_translate("FindAndReplaceDlg", "Wh&ole words", None))
        self.label_3.setText(_translate("FindAndReplaceDlg", "&Syntax", None))
        self.syntaxComboBox.setItemText(0, _translate("FindAndReplaceDlg", "Literal text", None))
        self.syntaxComboBox.setItemText(1, _translate("FindAndReplaceDlg", "Regular expression_r", None))
        self.findButton.setText(_translate("FindAndReplaceDlg", "&Find", None))
        self.replaceButton.setText(_translate("FindAndReplaceDlg", "&Replace", None))
        self.replaceAllButton.setText(_translate("FindAndReplaceDlg", "Replace &All", None))
        self.closeButton.setText(_translate("FindAndReplaceDlg", "Close", None))


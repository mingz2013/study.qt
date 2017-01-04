// mainwindow.h
// helloworld工程主窗口类头文件
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTextEdit;                                // 组件声明
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:                                  // slots表示在此私有函数声明域中声明的成员函数是一个“槽”，“槽”是一个完成类似回调函数功能的成员函数
    void slotInitializeTextEdit();              // 初始化文本编辑器内容的槽
    
private:
    Ui::MainWindow *ui;
    QTextEdit *m_QtextEdit;                     // 程序主工作区的文本编辑框组件
};

#endif // MAINWINDOW_H

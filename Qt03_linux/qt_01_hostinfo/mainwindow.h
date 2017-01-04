#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitWidget1();
    void InitWidget2();

public slots:
    void show11();
    
private:
    Ui::MainWindow *ui;

    QLineEdit *name;
    QLineEdit *ip;
    QWidget* widget1;
    QWidget* widget2;

    QTextEdit *detail;
    QPushButton *detailBtn;


};

#endif // MAINWINDOW_H

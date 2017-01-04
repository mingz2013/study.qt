#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTime>
#include <QTimeEdit>
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
    
private slots:
    void handleButton();

private:
    Ui::MainWindow *ui;

    QLabel *currentLabel;
    QTime timeNow;
    QTimeEdit *timeEdit;
    QPushButton *click_btn;
};

#endif // MAINWINDOW_H

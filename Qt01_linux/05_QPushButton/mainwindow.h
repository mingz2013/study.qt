#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void handleButton();            // 定义槽

private:
    Ui::MainWindow *ui;
    QPushButton *click_btn;
    QPushButton *flat_btn;
    QPushButton *menu_btn;
};

#endif // MAINWINDOW_H

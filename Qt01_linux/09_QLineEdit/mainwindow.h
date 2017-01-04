#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
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
    void handleButton();// 定义槽

private:
    Ui::MainWindow *ui;

    QLabel *nameLabel;
    QLabel *pswdLabel;
    QLabel *readOnlyLabel;
    QLabel *validatorLabel;
    QLineEdit *nameEdit;
    QLineEdit *pswdEdit;
    QLineEdit *readOnlyEdit;
    QLineEdit *validatorEdit;
    QPushButton *ok_btn;

};

#endif // MAINWINDOW_H

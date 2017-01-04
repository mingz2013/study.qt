#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:
    void on_pushButton_A_Close_clicked();

    void on_pushButton_B_Close_clicked();

    void on_pushButton_C_Close_clicked();

    void on_pushButton_A_clicked();

    void on_pushButton_B_clicked();

    void on_pushButton_C_clicked();

    void on_pushButton_SYS_Close_clicked();

    void on_pushButton_Lock_clicked();

private:
    Ui::Dialog *ui;
    bool isLock;

    QPoint windowPos, dPos, mousePos;// 移动相关

        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
};

#endif // DIALOG_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void InitWidget1();
    void InitWidget2();
public slots:
    void show11();
    
private:
    Ui::Dialog *ui;
    QWidget *widget1;
    QWidget *widget2;
    QLineEdit *name;
    QLineEdit *password;
    QPushButton *loginBtn;
    QPushButton *detailBtn;
    QRadioButton *rb1;
    QRadioButton *rb2;

};

#endif // DIALOG_H

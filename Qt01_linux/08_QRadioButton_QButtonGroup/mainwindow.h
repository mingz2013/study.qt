#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QTextEdit>

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
    void changeCurrentIndex(QAbstractButton *btn1);//改变

private:
    Ui::MainWindow *ui;
    QGridLayout *layout;
    QVBoxLayout *mainLayout;
    QGroupBox *gb;
    QButtonGroup *btnGroup;
    QRadioButton *rb1;
    QRadioButton *rb2;
    QTextEdit *m_QtextEdit;

};

#endif // MAINWINDOW_H

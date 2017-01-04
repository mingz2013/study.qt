#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScriptEngine>
#include <QScriptValue>

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
    void on_pushButton_clicked();

signals:
    void setString(QString text1, QString text2);

private:
    Ui::MainWindow *ui;

    QString doJS(QString m_password, QString m_vCode, QString verifycodeHex);

};

#endif // MAINWINDOW_H

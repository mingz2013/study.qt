#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include<QByteArray>

namespace Ui
{
    class MainWindow;
}

class MainWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void finished(QNetworkReply *reply);
    void DoHttpGet();
    void activateGetWidgets();
    void HideWidgets();
    void clearWidgets();
    void activatePostWidgets();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *nam;

};

#endif // MAINWINDOW_H

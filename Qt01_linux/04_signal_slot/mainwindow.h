#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

signals:                        // 信号
    void sng_txtEdit_txtEdit();

private slots:                  // 槽
    void on_m_btn_disconnect_clicked();
    void on_m_btn_connect_clicked();
};

#endif // MAINWINDOW_H

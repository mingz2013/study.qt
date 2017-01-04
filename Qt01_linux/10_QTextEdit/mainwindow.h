#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>

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
    void documentHasModified();
    void documentHasModified_LeaveWord(const QString&);

private:
    Ui::MainWindow *ui;
    QTextEdit *m_QtextEdit;
    QLineEdit *m_QLineEdit_LeaveWord;
    QTextEdit *m_QtextEdit_LeaveWord;
};

#endif // MAINWINDOW_H

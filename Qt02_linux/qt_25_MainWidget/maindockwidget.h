#ifndef MAINDOCKWIDGET_H
#define MAINDOCKWIDGET_H

#include <QDockWidget>
#include <QEventLoop>

namespace Ui {
class MainDockWidget;
}

class MainDockWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit MainDockWidget(QWidget *parent = 0);
    ~MainDockWidget();
    //int result()const {return m_result;}
    //int exec();
    QWidget *w;

public slots:
    //void exec();
    
private:
    Ui::MainDockWidget *ui;
    //QEventLoop * m_loop;
    //int m_result;


   // void setVisible(bool visible);
    void Init();
    void resizeEvent(QResizeEvent *e);
};

#endif // MAINDOCKWIDGET_H

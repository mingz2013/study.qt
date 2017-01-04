#ifndef POP_DOCKWIDGET_H
#define POP_DOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class Pop_DockWidget;
}

class Pop_DockWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit Pop_DockWidget(QWidget *parent = 0);
    ~Pop_DockWidget();
    
private:
    Ui::Pop_DockWidget *ui;
};

#endif // POP_DOCKWIDGET_H

#ifndef CHATBOX_DOCKWIDGET_H
#define CHATBOX_DOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class chatBox_DockWidget;
}

class chatBox_DockWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit chatBox_DockWidget(QWidget *parent = 0);
    ~chatBox_DockWidget();
    
private:
    Ui::chatBox_DockWidget *ui;
};

#endif // CHATBOX_DOCKWIDGET_H

#include "mainwindow.h"
#include <QApplication>
#include "chatbox_dockwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    chatBox_DockWidget chatBox;
    chatBox.show();
    
    return a.exec();
}

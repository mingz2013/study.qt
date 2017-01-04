#ifndef INIT_H
#define INIT_H

#include <QNetworkCookie>
#include <QString>
#include "chatbox_dockwidget.h"






typedef struct Other_Struct{
    QList<chatBox_DockWidget*> chatBox_List;    // 窗口指针列表
    QList<chatBox_DockWidget*> groupBox_List;    // 群窗口指针列表
    //QList<chatBox_DockWidget*> groupMemberBox_List;    // 群好友指针列表
//    QJsonObject myselfInfo; // 个人信息
}OTHER;


#endif // INIT_H

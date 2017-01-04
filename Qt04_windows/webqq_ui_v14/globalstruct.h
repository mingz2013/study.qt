#ifndef INIT_H
#define INIT_H

#include <QNetworkCookie>
#include <QString>
#include "chatdialog.h"
#include "groupchatdialog.h"
#include <QMap>
#include <QList>
#include "msgalertdialog.h"







typedef struct Other_Struct{
    QList<ChatDialog*> chatDialog_List;    // 窗口指针列表
    QList<GroupChatDialog*> groupDialog_List;    // 群窗口指针列表
    QList<MsgAlertDialog*> msgAlertDialog_List; // 提示框列表
    //    QJsonObject myselfInfo; // 个人信息
    QMap<QString, QList<QJsonObject> > puttyMsgMap;
    QMap<QString, QList<QJsonObject> > groupMsgMap;
}OTHER;


#endif // INIT_H

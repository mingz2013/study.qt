#include "maindialog.h"
#include "ui_maindialog.h"
#include <QMouseEvent>
#include <QDebug>
#include "globalset.h"
#include "chatdialog.h"
#include "groupchatdialog.h"
#include <QMenu>
#include "tools.h"

Q_DECLARE_METATYPE(QJsonObject)// 声明类型,以便var.setvalue()
extern GlobalSet globalset;// 引用全局变量

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    Init();
}

MainDialog::~MainDialog()
{
    delete ui;
}
void MainDialog::mouseMoveEvent(QMouseEvent *event){
    this->move(event->globalPos() - this->dPos);
    QDialog::mouseMoveEvent(event);
}

void MainDialog::mousePressEvent(QMouseEvent *event){
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
    QDialog::mousePressEvent(event);
}

void MainDialog::Init()
{
    qDebug() << "Init()";
    //ui->dockWidgetContents->setGeometry(0, 0, 240, 500);不管用
    //ui->label_MyAvatar->setGeometry(5, 5, 80, 80);
    //ui->comboBox_MyStateShow->setGeometry(86, 5, 40, 27);
    //ui->label_MyNick->setGeometry(127, 5, ui->dockWidgetContents->width() - 127 - 5, 27);
    //ui->label_MySignature->setGeometry(86, 38,ui->dockWidgetContents->width() - 86 - 5, 47);
    //ui->tabWidget->setGeometry(5, 86, ui->dockWidgetContents->width() - 10, ui->dockWidgetContents->height() - 86);
    ui->treeWidget_BuddyList->setGeometry(ui->tab_BuddyList->x(), ui->tab_BuddyList->y() , ui->tab_BuddyList->width(), ui->tab_BuddyList->height() - 1);
    ui->listWidget_GroupList->setGeometry(ui->tab_GroupList->x(), ui->tab_GroupList->y() , ui->tab_GroupList->width(), ui->tab_GroupList->height() - 1);
    ui->listWidget_RecentList->setGeometry(ui->tab_RecentList->x(), ui->tab_RecentList->y() , ui->tab_RecentList->width(), ui->tab_RecentList->height() - 1);



}

void MainDialog::mainDialogShowSlots()
{
    qDebug() << "窗体显示后执行";

    CreatTrayIcon(); // 显示托盘菜单

    //poll2thread = new poll2Thread(this);
    connect(globalset.webqq, SIGNAL(lninkSignal(QString)), this, SLOT(webqq_lnick_Slots(QString)));
    connect(globalset.webqq, SIGNAL(friends_result_Signal(QJsonObject)), this, SLOT(webqq_friends_result_Slots(QJsonObject)));
    connect(globalset.webqq, SIGNAL(qun_result_Signal(QJsonObject)), this, SLOT(webqq_qun_result_Slots(QJsonObject)));
    connect(globalset.webqq, SIGNAL(onlinelist_Signal(QJsonArray)), this, SLOT(webqq_onlinelist_Slots(QJsonArray)));
    connect(globalset.webqq, SIGNAL(poll2_obj_Signal(QJsonObject)), this, SLOT(webqq_poll2_obj_Slots(QJsonObject)));


    //poll2thread->start();
    globalset.webqq->startPoll2Thread();

    ui->label_MyNick->setText(globalset.webqq->nick);// 设置昵称

    globalset.webqq->get_single_long_nick2();    // 获取个性签名

    globalset.webqq->post_get_user_friends2(); // 获取好友列表

    globalset.webqq->post_get_group_name_list_mask2(); // 获取群列表
    globalset.webqq->get_online_buddies2();  // 获取在线好友列表
    globalset.webqq->get_friend_info2();     // 获取个人信息

}

void MainDialog::on_pushButton_Close_clicked()
{
    this->close();
}

void MainDialog::on_pushButton_Minisize_clicked()
{
    this->setHidden(true);
}

/**
 *个性签名获取到的槽
**/
void MainDialog::webqq_lnick_Slots(QString lnick)
{
    ui->label_MySignature->setText(lnick);
}
/**
 *接受好友分组的槽
**/
void MainDialog::webqq_friends_result_Slots(QJsonObject friends_result)
{

    QJsonArray friends = friends_result.value("friends").toArray();
    marknames = friends_result.value("marknames").toArray();
    QJsonArray categories = friends_result.value("categories").toArray();// 分组
    QJsonArray vipinfo = friends_result.value("vipinfo").toArray();
    info = friends_result.value("info").toArray();
    // 显示分组
    //QTreeWidgetItem* A = new QTreeWidgetItem(QStringList()<<"我的好友");
    //ui->treeWidget_BuddyList->addTopLevelItem(A);
    QList<QTreeWidgetItem*> topList;

    //topList.insert(0, new QTreeWidgetItem(QStringList() << "我的好友"));

    QList<int> index_List;
    index_List.clear();
    topList.insert(0, new QTreeWidgetItem(QStringList() << "在线好友"));// 插入在线好友

    for (int row = 0; row < categories.size(); row++)   // 插入接收到的分组
    {
        QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << categories[row].toObject().value("name").toString());
        QVariant varData;
        varData.clear();
        varData.setValue(categories[row].toObject());
        //Item->setData(0, Qt::UserRole, var);
        int index = (int)categories[row].toObject().value("index").toDouble();
        index_List.append(index);
        topList.insert(index + 1, Item);
    }
    QList<int> hide_List;// 要隐藏的分组
    if(!index_List.contains(0)){
        topList.insert(1, new QTreeWidgetItem(QStringList() << "我的好友"));
        //QVariant var;
        //var.setValue(categories[row]);
        //Item->setData(0, Qt::UserRole, var);
        //topList.value(1)->setData(0, Qt::UserRole, var);
        hide_List.append(1);
    }
    if(!index_List.contains(1)){
        topList.insert(2, new QTreeWidgetItem(QStringList() << "朋友"));
        hide_List.append(2);
    }
    if(!index_List.contains(2)){
        topList.insert(3, new QTreeWidgetItem(QStringList() << "家人"));
        hide_List.append(3);
    }
    if(!index_List.contains(3)){
        topList.insert(4, new QTreeWidgetItem(QStringList() << "同学"));
        hide_List.append(4);
    }
    topList.insert(11, new QTreeWidgetItem(QStringList() << "陌生人"));
    topList.insert(14, new QTreeWidgetItem(QStringList() << "黑名单"));

    ui->treeWidget_BuddyList->addTopLevelItems(topList);

    // 隐藏分组
    for(QList<int>::iterator it = hide_List.begin(); it != hide_List.end(); it++)
    {
        ui->treeWidget_BuddyList->topLevelItem(*it)->setHidden(true);
        qDebug() << "it--------->" << *it;
    }

    // 插入好友
    for(int row = 0; row < friends.size(); row++)
    {
        //qDebug() << "type------------->" << friends[row].toObject().value("categories").toDouble();
        int cat = (int)friends[row].toObject().value("categories").toDouble();
        qDebug() << "cat------->" << cat;
        QString nick = info[row].toObject().value("nick").toString();
        for(int i = 0; i < marknames.size(); i++)// 如果有备注名称，则改成备注名称
        {
            if(friends[row].toObject().value("uin") == marknames[i].toObject().value("uin"))
            {
                nick = marknames[i].toObject().value("markname").toString();
                break;
            }
        }
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(nick));
        QVariant var;
        var.setValue(info[row].toObject());
        item->setData(0, Qt::UserRole, var);
        topList.value(cat + 1)->addChild(item);


    }


}
/**
 *接受群分组的槽
**/
void MainDialog::webqq_qun_result_Slots(QJsonObject qun_result)
{
    QJsonArray gmasklist = qun_result.value("gmasklist").toArray();
    QJsonArray gnamelist = qun_result.value("gnamelist").toArray();
    QJsonArray gmarklist = qun_result.value("gmarklist").toArray();

    for(int row = 0; row < gnamelist.size(); row++)
    {
        QString gname = gnamelist[row].toObject().value("name").toString();
        for(int i = 0; i < gmarklist.size(); i++)
        {
            if(gnamelist[row].toObject().value("gid") == gmarklist[i].toObject().value("uin"))
            {
                gname = gmarklist[i].toObject().value("markname").toString();
            }
        }

        qDebug() << gname;
        ui->listWidget_GroupList->insertItem(row, new QListWidgetItem(gname));
        QVariant var;
        var.setValue(gnamelist[row].toObject());
        ui->listWidget_GroupList->item(row)->setData(Qt::UserRole, var);

    }


}
/**
 *接受在线好友列表的槽
**/
void MainDialog::webqq_onlinelist_Slots(QJsonArray onlineList)
{

    // 插入在线好友
    QList<QTreeWidgetItem*> onlineItemList;
    for(int row = 0; row < onlineList.size(); row++)
    {
        QString nick = NULL;
        QJsonValue uin = onlineList[row].toObject().value("uin");
        int r = 0;
        for(int j = 0; j < info.size(); j++)
        {
            if(uin == info[j].toObject().value("uin"))
            {
                nick = info[j].toObject().value("nick").toString();
                r = j;
                break;
            }
        }

        for(int i = 0; i < marknames.size(); i++)// 如果有备注名称，则改成备注名称
        {
            if(uin == marknames[i].toObject().value("uin"))
            {
                nick = marknames[i].toObject().value("markname").toString();
                break;
            }
        }
        onlineItemList.insert(row, new QTreeWidgetItem(QStringList(nick)));
        QVariant varData;
        varData.setValue(info[r].toObject());
        onlineItemList.value(row)->setData(0, Qt::UserRole, varData);
    }
    ui->treeWidget_BuddyList->topLevelItem(0)->insertChildren(0, onlineItemList);



}


/**
 *接收线程返回的数据的槽函数
**/
void MainDialog::webqq_poll2_obj_Slots(QJsonObject obj)
{


    if(obj.value("retcode").toBool() != false) {qDebug() << "get poll2 data wrong"; return;}

    QJsonArray result = obj.value("result").toArray();
    qDebug() << "result----------->" << result;

    for(int row = 0; row < result.size(); row++)
    {
        QJsonObject item = result[row].toObject();
        QString poll_type = item.value("poll_type").toString();
        QJsonObject item_value = item.value("value").toObject();


        if(poll_type == QString("buddies_status_change")){
            // 好友在线状态改变,对好友列表进行处理
        }else if(poll_type == QString("message")){
            // 好友消息，如果对话框已经打开，则发送信号，如果没有打开，则弹窗提示消息------
            QString from_uin = QString::number((qulonglong)item_value.value("from_uin").toDouble());
            ChatDialog* chatDialog_it;
            foreach (chatDialog_it, globalset.other_struct.chatDialog_List){
                if(chatDialog_it->uin == from_uin){ // 已打开
                    emit message_Signal(item_value);
                    setFocusProxy(chatDialog_it);
                    return;
                }
            }

            // 弹出提示框，然后继续往下执行
            // 如果提示框已经打开，直接显示消息，并且获取焦点
            // 否则新建提示框显示
            MsgAlertDialog* msgAlertDialog_it;
            bool isExist = false;
            foreach (msgAlertDialog_it, globalset.other_struct.msgAlertDialog_List){
                if(msgAlertDialog_it->from_uin == from_uin){ // 已打开
                    msgAlertDialog_it->setMsg(item_value);
                    setFocusProxy(msgAlertDialog_it);
                    isExist = true;
                    break;
                }
            }
            if(!isExist){
                MsgAlertDialog* msgAlertDialog = new MsgAlertDialog(item_value);
                msgAlertDialog->show();
                QRect DisktopRect = Tools::getDesktopRect();
                QPoint *msgPoint = new QPoint(msgAlertDialog->width(), msgAlertDialog->height());
                msgAlertDialog->move(DisktopRect.bottomRight() - *msgPoint);
                globalset.other_struct.msgAlertDialog_List.append(msgAlertDialog);
            }


            QMap<QString,QList<QJsonObject> >::iterator it; //遍历map
            for(it = globalset.other_struct.puttyMsgMap.begin(); it != globalset.other_struct.puttyMsgMap.end(); ++it )
            {
                if(it.key() == from_uin){   // 没打开，但列表中有，直接加入
                    it.value().append(item_value);
                    return;
                }
            }
            // 没打开，列表也没有，新建列表，加入map
            QList<QJsonObject> MsgList;
            MsgList.append(item_value);
            globalset.other_struct.puttyMsgMap.insert(from_uin, MsgList);



        }else if(poll_type == QString("group_message")){
            // qun消息，如果对话框已经打开，则发送信号，如果没有打开，则弹窗提示消息-------
            QString from_uin = QString::number((qulonglong)item_value.value("from_uin").toDouble());
            GroupChatDialog* groupChatDialog_it;
            foreach (groupChatDialog_it, globalset.other_struct.groupDialog_List){
                if(groupChatDialog_it->group_uin == from_uin){
                    emit group_message_Signal(item_value);
                    setFocusProxy(groupChatDialog_it);
                    return;
                }
            }

            // 弹出提示框，然后继续往下执行
            // 如果提示框已经打开，直接显示消息，并且获取焦点
            // 否则新建提示框显示
            MsgAlertDialog* msgAlertDialog_it;
            bool isExist = false;
            foreach (msgAlertDialog_it, globalset.other_struct.msgAlertDialog_List){
                if(msgAlertDialog_it->from_uin == from_uin){ // 已打开
                    msgAlertDialog_it->setMsg(item_value);
                    setFocusProxy(msgAlertDialog_it);
                    isExist = true;
                    break;
                }
            }
            if(!isExist){
                MsgAlertDialog* msgAlertDialog = new MsgAlertDialog(item_value);
                msgAlertDialog->show();
                QRect DisktopRect = Tools::getDesktopRect();
                QPoint *msgPoint = new QPoint(msgAlertDialog->width(), msgAlertDialog->height());
                msgAlertDialog->move(DisktopRect.bottomRight() - *msgPoint);
                globalset.other_struct.msgAlertDialog_List.append(msgAlertDialog);
            }


            QMap<QString,QList<QJsonObject> >::iterator it; //遍历map
            for(it = globalset.other_struct.groupMsgMap.begin(); it != globalset.other_struct.groupMsgMap.end(); ++it )
            {
                if(it.key() == from_uin){
                    it.value().append(item_value);
                    return;
                }
            }
            QList<QJsonObject> MsgList;
            MsgList.append(item_value);
            globalset.other_struct.groupMsgMap.insert(from_uin, MsgList);

        }else{
            // wrong
        }
    }




}

/**
 *窗口关闭事件
**/
void MainDialog::closeEvent(QCloseEvent *event)
{
    globalset.webqq->stopPoll2Thread();
    if (myTrayIcon->isVisible())
       {
           myTrayIcon->showMessage("webQQ","webQQ, by MingZz ! QQ:xxx",QSystemTrayIcon::Information,5000);

           hide();     //最小化
           event->ignore();
       }
       else
           event->accept();


    QDialog::closeEvent(event);
}


/**
 *好友treewidget被单击
**/
void MainDialog::on_treeWidget_BuddyList_itemPressed(QTreeWidgetItem *item, int column)
{

    if (qApp->mouseButtons() == Qt::LeftButton)// 左键单击 弹出聊天菜单
    {
        if (item->childCount() > 0) { return; }// 如果是父级菜单
        // 不可重复为同一联系人打开多个窗口-----？？？？？建立一个列表QList<chatBox_DockWidget*>
        ChatDialog* chatDialog_it;
        foreach (chatDialog_it, globalset.other_struct.chatDialog_List){
            if(chatDialog_it->var_chatDialog == item->data(0, Qt::UserRole)){
                // 如果窗口已打开，则将其获取焦点----------------------------------------???????????????????????????
                setFocusProxy(chatDialog_it);
                return;
            }
        }
        // 如果窗口未打开，则打开窗口，并加入列表
        qDebug() << "item->data()------>" << item->data(0, Qt::UserRole);
        ChatDialog *chatDialog = new ChatDialog(item->data(0, Qt::UserRole));
        connect(this, SIGNAL(message_Signal(QJsonObject)), chatDialog, SLOT(message_Slot(QJsonObject)));
        globalset.other_struct.chatDialog_List.insert(0, chatDialog);
        chatDialog->show();
    }
    else if (qApp->mouseButtons() == Qt::RightButton)// 右键单击
    {
        if (item->childCount() > 0) { return; }// 如果是父级菜单
        //ShowMenu();
        //QPoint pos;
        QMenu menu(ui->treeWidget_BuddyList);
        QIcon myIcon("images/boy.ico");
        menu.addAction(myIcon,tr("发送即时消息"));
        menu.addAction(myIcon,tr("发送电子邮件"));
        menu.addAction(myIcon,tr("访问QQ空间"));
        menu.addAction(myIcon,tr("创建桌面联系人"));
        menu.addAction(myIcon,tr("移动联系人至"));
        menu.addAction(myIcon,tr("删除好友"));
        menu.addAction(myIcon,tr("修改备注"));
        menu.addAction(myIcon,tr("隐身设置"));
        menu.addAction(myIcon,tr("消息记录"));
        menu.addAction(myIcon,tr("查看资料"));
        menu.exec(QCursor::pos());
    }

}

/**
 *QQ群listwidget被单击
**/
void MainDialog::on_listWidget_GroupList_itemPressed(QListWidgetItem *item)
{

    if (qApp->mouseButtons() == Qt::LeftButton)
    {
        GroupChatDialog* groupChatDialog_it;
        foreach (groupChatDialog_it, globalset.other_struct.groupDialog_List){
            if(groupChatDialog_it->var_groupChatDialog == item->data(Qt::UserRole)){
                // 如果窗口已打开，则将其获取焦点----------------------------------------???????????????????????????
                setFocusProxy(groupChatDialog_it);
                return;
            }
        }
        // 如果窗口未打开，则打开窗口，并加入列表
        GroupChatDialog *groupChatDialog = new GroupChatDialog(item->data(Qt::UserRole));
        connect(this, SIGNAL(group_message_Signal(QJsonObject)), groupChatDialog, SLOT(group_message_Slot(QJsonObject)));
        globalset.other_struct.groupDialog_List.insert(0, groupChatDialog);
        groupChatDialog->show();
    }
    else if (qApp->mouseButtons() == Qt::RightButton)
    {
        //if (item->childCount() > 0) { return; }// 如果是父级菜单
        //ShowMenu();
        //QPoint pos;
        QMenu menu(ui->listWidget_GroupList);
        QIcon myIcon("images/boy.ico");
        menu.addAction(myIcon,tr("发送群消息"));
        menu.addSeparator();     //加入一个分离符
        menu.addAction(myIcon,tr("访问群社区"));
        menu.addAction(myIcon,tr("查看群资料"));
        menu.addAction(myIcon,tr("查看消息记录"));
        menu.addAction(myIcon,tr("接收并提示群消息"));
        menu.addAction(myIcon,tr("接收不提示群消息"));
        menu.addAction(myIcon,tr("完全阻止群消息"));
        menu.addAction(myIcon,tr("创建桌面联系人"));
        menu.addAction(myIcon,tr("退出该群"));
        menu.exec(QCursor::pos());
    }

}


void MainDialog::CreatTrayMenu()
{
    //miniSizeAction = new QAction("最小化(&N)",this);
    //maxSizeAction = new QAction("最大化(&X)",this);
    restoreWinAction = new QAction("还 原(&R)",this);
    quitAction = new QAction("退出(&Q)",this);

    //this->connect(miniSizeAction,SIGNAL(triggered()),this,SLOT(hide()));
   // this->connect(maxSizeAction,SIGNAL(triggered()),this,SLOT(showMaximized()));
    connect(restoreWinAction,SIGNAL(triggered()),this,SLOT(showNormal()));
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));

    myMenu = new QMenu((QWidget*)QApplication::desktop());

    //myMenu->addAction(miniSizeAction);
    //myMenu->addAction(maxSizeAction);
    myMenu->addAction(restoreWinAction);
    myMenu->addSeparator();     //加入一个分离符
    myMenu->addAction(quitAction);
}

void MainDialog::CreatTrayIcon()
{
    CreatTrayMenu();

    if (!QSystemTrayIcon::isSystemTrayAvailable())      //判断系统是否支持系统托盘图标
    {
        return;
    }

    myTrayIcon = new QSystemTrayIcon(this);

    myTrayIcon->setIcon(QIcon(":/login/Resources/QQ.png"));   //设置图标图片
    //setWindowIcon(QIcon("mytrayIcon.ico"));  //把图片设置到窗口上

    myTrayIcon->setToolTip("webQQ v1.0");    //托盘时，鼠标放上去的提示信息

    myTrayIcon->showMessage("webQQ","webQQ, by MingZz ! QQ:xxx",QSystemTrayIcon::Information,10000);



    myTrayIcon->setContextMenu(myMenu);     //设置托盘上下文菜单

    myTrayIcon->show();
    this->connect(myTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainDialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:

    case QSystemTrayIcon::DoubleClick:
        showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        myTrayIcon->showMessage("webQQ","webQQ, by MingZz ! QQ:xxx",QSystemTrayIcon::Information,10000);
        break;

    default:
        break;
    }
}



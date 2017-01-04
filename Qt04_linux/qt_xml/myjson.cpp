#include "myjson.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <QDebug>

myjson::myjson(QWidget *parent) :
    QWidget(parent)
{

    QJsonObject root;
    QJsonValue root_value;

    QJsonValue value;

    QVariant var;
    var.setValue(QString("hhhhhhhhhh"));
    value = QJsonValue::fromVariant(var);

    root.insert(QString("config"), value);

    qDebug() << "root---->" << root;

    QJsonValue v;



    //QJsonDocument doc;
    //doc.fromJson();




}

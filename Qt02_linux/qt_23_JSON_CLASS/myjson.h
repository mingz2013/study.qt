#ifndef MYJSON_H
#define MYJSON_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonValueRef>
#include <QString>
#include <QDebug>
#include <QFile>

class MyJson : public QObject
{
    Q_OBJECT
public:
    explicit MyJson(QObject *parent = 0);
    static bool getObject(const QString &strJson, QJsonObject &object);
    static bool getObjectFromFile(const QString &filename, QJsonObject &object);
    
};

#endif // MYJSON_H

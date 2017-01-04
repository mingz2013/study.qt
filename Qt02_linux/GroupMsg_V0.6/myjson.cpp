#include "myjson.h"

MyJson::MyJson(QObject *parent) :
    QObject(parent)
{
}

/**
 *函数名：getObject
 *  参数1：QString类型字串
 *  参数2：QJsonObject类型指针
 *  返回值：bool型
 *  作用：从字符串获取json对象，并付给 对象指针，成功返回true，失败返回false
**/
bool MyJson::getObject(const QString &strJson, QJsonObject &object)
{
    QJsonParseError jsonpe;
    QByteArray byte;
    byte.append(strJson.toUtf8());
    QJsonDocument json = QJsonDocument::fromJson(byte, &jsonpe);
    if (jsonpe.error == QJsonParseError::NoError)
    {
        if (json.isObject())
        {
            QJsonObject obj = json.object();
            if (obj.contains("error"))
            {
                qDebug() << "error:" << obj["error"];
            }else{
                object = obj;
                return true;
            }
        }else{
            qDebug() << "error, shoud json object";
        }
    }else{
        qDebug() << "error:" << jsonpe.errorString();
    }
    return false;
}

/**
 *函数名：getObject
 *  参数1：QString类型文件名
 *  参数2：QJsonObject类型指针
 *  返回值：bool型
 *  作用：从文件获取json对象，并付给 对象指针，成功返回true，失败返回false
**/
bool MyJson::getObjectFromFile(const QString &filename, QJsonObject &object)
{
    QString strJson;
    QFile file;
    file.setFileName(filename);

    bool success = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!success)
    {
        qDebug() << "file open failed------in MyJson::getObjectFromFile()";
        return false;
    }
    strJson = file.readAll();
    file.close();

    return getObject(strJson, object);
}

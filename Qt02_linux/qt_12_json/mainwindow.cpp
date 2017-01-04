#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonValueRef>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    QString settings;
    QFile file;
    file.setFileName("/tmp/settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();
    */
    settings = "{"
                      "  \"Herausgeber\": \"Xema\","
                      "  \"Nummer\": \"1234-5678-9012-3456\","
                      "  \"Deckung\": 2e+6,"
                      "  \"Währung\": \"EURO\","
                      "  \"Kinder\": [\"Reiten\", \"Golfen\", \"Lesen\" ],"
                      "  \"Kinder1\": ["
                      "                 \"Reiten\","
                      "                 \"Golfen\","
                      "                 \"Lesen\" "
                      "                 ],"
                      "  \"Inhaber\": {"
                      "    \"Name\": \"Mustermann\","
                      "    \"Vorname\": \"Max\","
                      "    \"männlich\": true,"
                      "    \"Hobbys\": [ \"Reiten\", \"Golfen\", \"Lesen\" ],"
                      "    \"Alter\": 42,"
                      "    \"Kinder\": [\"Reiten\", \"Golfen\", \"Lesen\" ],"
                      "    \"Partner\": null"
                      "  }"
                      "}";

    QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
    qWarning() << sd.isNull(); // <- print false :)
    QJsonObject sett2 = sd.object();
    qWarning() << sett2.value(QString("Nummer"));
    qWarning() << sett2.value(QString("Inhaber"));  // <- print my title


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QJsonParseError jsonpe;
    QByteArray byte;
    byte.append(settings);
    QJsonDocument json = QJsonDocument::fromJson(byte, &jsonpe);
    if (jsonpe.error == QJsonParseError::NoError)
    {
        if (json.isObject())
        {
            QJsonObject obj = json.object();
            if (obj.contains("error"))
            {
                qDebug() << "error:" << obj["error"];
            }
            else
            {
               // qDebug() << "obj[Inhaber]---------->" << obj["Inhaber"];
                QJsonArray jarray = obj["Kinder1"].toArray();
                qDebug() << "jarray--------------->" << jarray.empty();
                qDebug() << "type" << obj["Kinder"].type();
                qDebug() << "obj[\"Kinder\"]------->" << obj.value(QString("Kinder"));
               // qDebug() << "obj[\"Inhaber\"].toobject()------->" << obj["Inhaber"].toObject();
                for (int row = 0; row < jarray.size(); row++)
                {
                    qDebug() << "====Row[" << row << "] Start===================";
                    qDebug() << "jarray[row]------->" << jarray[row];
                    QJsonObject jobj = jarray[row].toObject();
                    for (QJsonObject::Iterator it = jobj.begin(); it != jobj.end(); it++)
                    {
                        qDebug() << it.key() << " => " << it.value();
                    }
                }
            }
        }
        else
        {
            qDebug() << "error, shoud json object";
        }
    }
    else
    {
        qDebug() << "error:" << jsonpe.errorString();
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <myjson.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString strJson = "{"
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

    QJsonObject obj;

    bool success = MyJson::getObject(strJson, obj);
    if(!success)
    {
        qDebug() << "wrong";
        return;
    }
    QJsonValue Inhaber = obj.value("Inhaber");
    if(Inhaber.isNull())
    {
        qDebug() << "Inhaber is null";
        return;
    }
    qDebug() << "Inhaber---------->" << Inhaber;
    qDebug() << "Inhaber.type----->" << Inhaber.type();

    QJsonObject Inhaber_obj = Inhaber.toObject();

    if(Inhaber_obj.isEmpty())
    {
        qDebug() << "Inhaber_obj is empty";
        return;
    }
    QJsonValue Hobbys = Inhaber_obj.value("Hobbys");
    qDebug() << "hobbys----------->" << Hobbys;
    qDebug() << "hobbys.type------->" << Hobbys.type();

    QJsonArray hobbys_array = Hobbys.toArray();
    for(int row = 0; row < hobbys_array.size(); row++)
    {
        //qDebug() << row << hobbys_array[row];
        qDebug() << row << hobbys_array[row].toString();
    }

    for (QJsonObject::Iterator it = obj.begin(); it != obj.end(); it++)
    {
        qDebug() << "obj---->" << it.key() << " => " << it.value();
    }





}

MainWindow::~MainWindow()
{
    delete ui;
}

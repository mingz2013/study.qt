#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json/json.h"
#include <stdio.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString test ="{\"id\":1,\"name\":\"MingZznet\"}";
    Json::Reader reader;
    Json::Value value;
    if(reader.parse(test.toStdString(),value))
    {
        if(!value["id"].isNull())
        {
            qDebug() << value["id"].asInt();
            std::cout << value["name"].asString() << std::endl;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    using namespace std;

    std::string strValue = "{\"学号\":\"20120207001\",\"姓名\":\"张无忌\",\"性别\":\"男\"}";

    Json::Reader reader;
    Json::Value value;

    if (reader.parse(strValue, value))
    {
       std::string out = value["学号"].asString();
       std::cout << out << std::endl;

       out = value["姓名"].asString();
       std::cout << out << std::endl;

       out = value["性别"].asString();
       std::cout << out << std::endl;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    std::string settings = "{"
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
    Json::Reader reader;
    Json::Value value;

    if (reader.parse(settings, value))
    {
       std::string out = value["Herausgeber"].asString();
       std::cout << out << std::endl;

       std::cout << value["Kinder"] << std::endl;
       std::cout << value["Kinder"].type() << std::endl;
       std::cout << value["Kinder"].isArray() << std::endl;
       //std::string arr[] = value["Kinder"];

       //out = value["Inhaber"].asString();
       std::cout << value["Inhaber"] << std::endl;
       std::cout << value["Inhaber"].type() << std::endl;
       std::cout << value.isObject() << std::endl;

       //out = value["Inhaber"].asString();
       std::cout << out << std::endl;
    }

}

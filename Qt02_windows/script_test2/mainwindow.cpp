#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    QScriptEngine engine;
    QScriptValue func = engine.evaluate("(function(a, b) { return a+b;})");
    QScriptValueList args;
    args << 1 << 2;
    QScriptValue result = func.call(QScriptValue(), args);
    qDebug() << "Result: " << result.toInt32();


    /*
    QScriptEngine engine;
    QScriptValue object = engine.evaluate("(function add(a, b) {return a + b;})");
    QScriptValue add = engine.globalObject().property("add");
     qDebug() << add.call(QScriptValue(), QScriptValueList() << 1 << 2).toNumber(); // 3
    //qScriptConnect(this, SIGNAL(setString(QString,QString)), QScriptValue(), handler);


/*
     QScriptValue object = eng.evaluate("({ unitName: 'Celsius', toKelvin: function(x) { return x + 273; } })");
     QScriptValue toKelvin = object.property("toKelvin");
     QScriptValue result = toKelvin.call(object, QScriptValueList() << 100);
     qDebug() << result.toNumber(); // 373
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << doJS("gfsdgfdg","fsdgdg","asdsfds");
}

QString MainWindow::doJS(QString m_password, QString m_vCode, QString verifycodeHex)
{
    QString m_encodePassword = "";

        QFile _scriptFile(":/res/QQ.js");
        if (!_scriptFile.open(QIODevice::ReadOnly))
        {
            m_encodePassword.clear();
            qWarning() << "encodePass.js open failed";
            return NULL;
        }
        QTextStream _stream(&_scriptFile);
        QString _contents = _stream.readAll();
        _scriptFile.close();
        QScriptEngine _engine;
        QScriptValue _js = _engine.evaluate(_contents);
        QScriptValue _passwordEncoding = _engine.globalObject().property("func");
        QScriptValueList _args;
        _args << QScriptValue(m_password) << QScriptValue(m_vCode.toUpper()) << QScriptValue(verifycodeHex);
        m_encodePassword = _passwordEncoding.call(QScriptValue(), _args).toString();
        return m_encodePassword;
}

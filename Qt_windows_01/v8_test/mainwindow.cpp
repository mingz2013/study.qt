#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <private/v8.h>
#include <QDebug>
using namespace v8;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*

    HandleScope handle_scope;

    Persistent<Context> context = Context::New();
    Context::Scope context_scope(context);
    Handle<String> source = String::New("'Hello' + ', World!'");
    Handle<Script> script = Script::Compile(source);



    Handle<Value> result = script->Run();
    context.Dispose();

    String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
    */

    HandleScope handle_scope;
    TryCatch try_catch;

    Persistent<Context> context = Context::New();
    Context::Scope context_scope(context);
    Handle<String> funcname = String::New("func");
    Handle<Value> val = context->Global()->Get(funcname);
    if (!val->IsFunction()) return; // false;
    qDebug() << "is function";
    Handle<Function> fun = Handle<Function>::Cast(val);
    Handle<Value> result;
        Handle<String> str_x;
        Handle<String> str_y;
        Handle<String> str_z;
        Handle<Value> argv[] = { str_x, str_y, str_z};
        int argc = 3;
        result = fun->Call(context->Global(), argc, argv);
        //Handle<Value> argv_2[];// 要填个数
/*
        if(argc == 3){
            qDebug()  << "funcname is func";

            str_x = String::New(argv[0].data());
            str_y = String::New(argv[1].data());
            str_z = String::New(argv[2].data());
            Handle<Value> argv_2[] = { str_x, str_y, str_z};
            result = fun->Call(context->Global(), argc, argv_2);
        }else if(argc == 2){
            qDebug()  << "funcname is hash";
            qDebug() << argv[0].data() << argv[1].data();
            str_x = String::New(argv[0].data());
            str_y = String::New(argv[1].data());
            //Handle<String> str_z = String::New(argv[2]);
            Handle<Value> argv_3[] = { str_x, str_y};
            qDebug() << argc ;
            result = fun->Call(context->Global(), argc, argv_3);
        }else{
            qDebug()  << "funcname is wrong";
            //wrong
        }
*/
        if (result.IsEmpty()) {
            String::Utf8Value error(try_catch.Exception());

           // return QString("result is empty"); //false;
        } else {
            String::AsciiValue ascii(result);
           // return QString(*ascii);
            //return true;
        }
        context.Dispose();


}

MainWindow::~MainWindow()
{
    delete ui;
}

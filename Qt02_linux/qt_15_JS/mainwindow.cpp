#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <include/v8.h>
#include <stdio.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    using namespace v8;
    using namespace std;

    // Get the default Isolate created at startup.
     Isolate* isolate =Isolate::GetCurrent();

     // Create a stack-allocated handle scope.
     HandleScope handle_scope(isolate);

     // Create a new context.
     Handle<Context> context =Context::New(isolate);

     // Here's how you could create a Persistent handle to the context, if needed.
     Persistent<Context> persistent_context(isolate, context);

     // Enter the created context for compiling and
     // running the hello world script.
     Context::Scope context_scope(context);

     // Create a string containing the JavaScript source code.
     // 看到这句话，其实就是在加载一个js文件了。只不过这个js文件内容为：'Hello' + ', World!'
     //Handle<String> source =String::New("'Hello' + ', World!'");
     //Handle<String> source =String::New("helloworld.js");

     /************************************************************/
     //v8::Handle<v8::String> ReadJS(const char* name)
     //{
     const char* name = ".//helloworld.js";
     FILE* file = fopen(name, "rb");
     if (file == NULL) {
         //return v8::Handle<v8::String>();
         qDebug() << "file is NULL";
         return;
     }
     fseek(file, 0, SEEK_END);
     int size = ftell(file);
     rewind(file);
     char* chars = new char[size + 1];
     chars[size] = '\0';
     for (int i = 0; i < size;) {
         int read = fread(&chars[i], 1, size - i, file);
         i += read;
     }
     fclose(file);
     //v8::Handle<v8::String> source = v8::String::New(chars, size);
     v8::Handle<v8::String> source = v8::String::New(chars);
     delete[] chars;
     //return source;
     qDebug() << "return source";
     //}
     /*************************************************************/


       // 那么这里，source就已经是加载过的js文件字符串内容了，接下来V8需要对js进行编译解释。
     // Compile the source code.
     Handle<Script> script =Script::Compile(source);
     qDebug() << "get script";
     // Run the script to get the result.
     Handle<Value> result = script->Run();
     qDebug() << "run";
     // The persistent handle needs to be eventually disposed.
     persistent_context.Dispose();
     qDebug() << "Dispose";
     // Convert the result to an ASCII string and print it.
     String::AsciiValue ascii(result);
     qDebug() << "ascii";
     printf("%s\n",*ascii);
     qDebug() << "printf";
     qDebug() << *ascii;
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "v8_js.h"
#include <QDebug>
#include <iostream>
#include <QFile>

QT_BEGIN_NAMESPACE
extern Q_QML_EXPORT v8::Local<v8::Context> qt_QJSEngineV8Context(QJSEngine *);
extern Q_QML_EXPORT v8::Local<v8::Value> qt_QJSValueV8Value(const QJSValue &);
QT_END_NAMESPACE
#define TEST_FUNCTION_SOURCE "(function() { return 123; })"

V8_JS::V8_JS(QObject *parent) :
    QObject(parent)
{
}

/**
 *函数名：runJS
 *  参数1：char类型文件名指针
 *  参数2：char类型函数名指针
 *  参数3：int类型
 *  参数4：string类型数组
 *  作用：运行JS脚本，返回运行结果
**/
QString V8_JS::runJS(const char *filename, const char* funcname, const int argc,const string argv[])
{/*
    QString output;
    Persistent<Context> context_;
    TryCatch try_catch;
    Isolate* isolate = Isolate::GetCurrent();
    //v8::HandleScope handle_scope(isolate);
    v8::HandleScope handle_scope;
    //Handle<ObjectTemplate> global = ObjectTemplate::New();
    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
    //global->Set(String::New("log"), FunctionTemplate::New(LogCallback));

    //v8::Handle<v8::Context> context = v8::Context::New(isolate, NULL, global);
    v8::Persistent<v8::Context> context = v8::Context::New(NULL, global);

    Context::Scope context_scope(context);

   // context_.Reset(isolate, context);


   // v8::Handle<v8::String> source = v8::String::New(cmd.utf16());
    v8::Handle<v8::String> source = ReadFile(filename);
    if(source.IsEmpty()){qDebug() << "读取JS脚本失败！";return NULL;}

    v8::Handle<v8::Script> script = v8::Script::Compile(source);
    if (script.IsEmpty()) {
        output = QString::fromUtf16(*(v8::String::Value(try_catch.Exception())));
        qDebug() << output;
    } else {
        //v8::Handle<v8::Value> result = script->Run();
        Handle<String> str_funcname = String::New(funcname);
        Handle<Value> val = context->Global()->Get(str_funcname);
        if (!val->IsFunction()){
            qDebug() << "not is function";
            return "not is function"; // false;
        }
        qDebug() << "is function";
        v8::Handle<v8::Function> fun = v8::Handle<v8::Function>::Cast(val);
        Handle<Value> result;
        Handle<String> str_x;
        Handle<String> str_y;
        Handle<String> str_z;
        //Handle<Value> argv_2[];// 要填个数

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
        if (result.IsEmpty()) {
            output = QString::fromUtf16(*(v8::String::Value(try_catch.Exception())));
        } else {
            output = QString::fromUtf16(*(v8::String::Value(result)));
        }
    }
    context.Dispose();
    return output;
    */


    QString output;
    QString source;
    QFile file(QString(filename));
    if(file.open(QFile::ReadOnly)){
        source = QString(file.readAll());
    }
    file.close();


    QJSEngine eng;
    QJSValue fun = eng.evaluate(source);
    //QVERIFY(fun.isCallable());

    v8::HandleScope handleScope;
    v8::Local<v8::Context> context = qt_QJSEngineV8Context(&eng);
    v8::Context::Scope contextScope(context);

    v8::Local<v8::Function> v8fun = qt_QJSValueV8Value(fun).As<v8::Function>();
    v8::Local<v8::Object> v8thisObject = v8::Object::New();

    //QVERIFY(v8fun->Call(v8thisObject, /*argc=*/0, /*argv=*/0)->IsNumber());
    //QBENCHMARK {
     Handle<Value> result;
     Handle<String> str_x;
     Handle<String> str_y;
     Handle<String> str_z;
     if(argc == 3){
         qDebug()  << "funcname is func";

         str_x = String::New(argv[0].data());
         str_y = String::New(argv[1].data());
         str_z = String::New(argv[2].data());
         Handle<Value> argv_2[] = { str_x, str_y, str_z};
         //result = fun->Call(context->Global(), argc, argv_2);
          result = v8fun->Call(v8thisObject, /*argc=*/argc, /*argv=*/argv_2);

     }else if(argc == 2){
         qDebug()  << "funcname is hash";
         qDebug() << argv[0].data() << argv[1].data();
         str_x = String::New(argv[0].data());
         str_y = String::New(argv[1].data());
         //Handle<String> str_z = String::New(argv[2]);
         Handle<Value> argv_3[] = { str_x, str_y};
         qDebug() << argc ;
         //result = fun->Call(context->Global(), argc, argv_3);
          result = v8fun->Call(v8thisObject, /*argc=*/argc, /*argv=*/argv_3);
     }else{
         qDebug()  << "funcname is wrong";
         //wrong
     }
     if (result.IsEmpty()) {
       //  output = QString::fromUtf16(*(v8::String::Value(try_catch.Exception())));
     } else {
         output = QString::fromUtf16(*(v8::String::Value(result)));
     }

    //}



        return output;
}


/*
/**
 *读取文件功能
**//*
Handle<String> V8_JS::ReadFile(const string& name) {
  FILE* file = fopen(name.c_str(), "rb");
  if (file == NULL) return Handle<String>();

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
    i += read;
  }
  fclose(file);
  qDebug() << chars;
  Handle<String> result = String::New(chars, size);
  delete[] chars;
  return result;
}
*/

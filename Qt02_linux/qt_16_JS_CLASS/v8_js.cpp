#include "v8_js.h"
#include <QDebug>

v8_js::v8_js(QObject *parent) :
    QObject(parent)
{
}

QString v8_js::runJS(const char *name)
{
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
        //const char* name = ".//helloworld.js";
        FILE* file = fopen(name, "rb");
        if (file == NULL) {
            //return v8::Handle<v8::String>();
            qDebug() << "file is NULL";
            return QString("file is NULL");
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
        return QString(*ascii);
/*
        Handle<String> js_func_name ;
        Handle<Value>  js_func_val ;
        Handle<Function> js_func ;
        int argc = 2;
        Handle<Value>  argv[argc] ;
        Handle<Integer> int_x ;
        Handle<Integer> int_y ;

        // 这一句是创建函数名对象
        js_func_name = String::New("func") ;

        // 从全局运行环境中进行查找，看看是否存在一个叫做“OnClick”的函数
        js_func_val = persistent_context->Global()->Get(js_func_name) ;
        if(!js_func_val->IsFunction()) {
          //LOG("on_click, js_func_val->IsFunction check failed!") ;
            qDebug() << "on_click, js_func_val->IsFunction check failed!";
        } else {

        // 利用handle的强制类型转换，把js_func_val转换成一个函数对象
          js_func = Handle<Function>::Cast(js_func_val) ;

        // 初始化参数，所有数据都要定义成javascript可以识别的数据类型，例如Integer对象
        // javascript中是没有内建数据类型的（int, char, short是c/c++中的用的类型）
          int_x = Integer::New(x) ;
          int_y = Integer::New(y) ;

        // 把这些对象放到argv数组中去
          argv[0] = int_x ;
          argv[1] = int_y ;

        // 利用函数对象去调用该函数，当然需要传入脚本的运行环境，以及参数个数和参数的值。
         Handle<Value> sum = js_func->Call(persistent_context->Global(), argc, argv) ;
         String::AsciiValue sumascii(sum);
         return QString(*sumascii);
        }
        */
}



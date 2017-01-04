#include "v8_js.h"
#include <QDebug>
#include <iostream>

V8_JS::V8_JS(QObject *parent) :
    QObject(parent)
{
}

QString V8_JS::runJS(const char *filename, int x, int y)
{
    //Isolate* isolate_;
    Handle<String> string_;
    Handle<Script> script_;
    Persistent<Context> context_;
    Persistent<Function> process_;
    TryCatch try_catch;

    qDebug() << "runJS";
    Isolate* isolate = Isolate::GetCurrent();
    v8::HandleScope handle_scope(isolate);
    qDebug() << "handle_scope";

    Handle<ObjectTemplate> global = ObjectTemplate::New();
    global->Set(String::New("log"), FunctionTemplate::New(LogCallback));

    v8::Handle<v8::Context> context = v8::Context::New(isolate, NULL, global);

    Context::Scope context_scope(context);
    qDebug() << "context_scope";
    context_.Reset(isolate, context);
    qDebug() << "contex_reset";

    //Handle<String> process_name = String::New("Process");
    //Handle<String> filename = ReadFile(filename);
    string_ = ReadFile(filename);

    if(string_.IsEmpty())  return QString("file is emply");


    if (!ExecuteScript(string_))
        return QString("!ExecuteScript(script_)"); // false;
    qDebug() << "ExecuteScript";

    Handle<String> funcname = String::New("func");
    Handle<Value> val = context->Global()->Get(funcname);

    if (!val->IsFunction()) return QString("!val->IsFunction()"); // false;

    Handle<Function> fun = Handle<Function>::Cast(val);

    process_.Reset(isolate, fun);

    //return true;
    const int argc = 2;

    Handle<Integer> int_x ;
    Handle<Integer> int_y ;

    int_x = Integer::New(x) ;
    int_y = Integer::New(y) ;

    Handle<Value> argv[argc] = { int_x, int_y };

    Handle<Value> result = fun->Call(context->Global(), argc, argv);
    if (result.IsEmpty()) {
        String::Utf8Value error(try_catch.Exception());
        Log(*error);
        //std::cout << "result is empty" << std::endl;
        return QString("result is empty"); //false;
    } else {
        String::AsciiValue ascii(result);
        return QString(*ascii);
        //return true;
    }
}


bool V8_JS::ExecuteScript(Handle<String> string) {

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope handle_scope(isolate);
    qDebug() << "handle_scope";
    // We're just about to compile the script; set up an error handler to
    // catch any exceptions the script might throw.
    TryCatch try_catch;

    // Compile the script and check for errors.
    Handle<Script> compiled_script = Script::Compile(string);
    qDebug() << "compiled_script";
    if (compiled_script.IsEmpty()) {
      String::Utf8Value error(try_catch.Exception());
      Log(*error);
       qDebug() << "compied_script is empty";
      // The script failed to compile; bail out.
      return false;
    }
    qDebug() << "compied_script is not empty";
    // Run the script!
    Handle<Value> result = compiled_script->Run();
    if (result.IsEmpty()) {
      // The TryCatch above is still in effect and will have caught the error.
      String::Utf8Value error(try_catch.Exception());
      Log(*error);
      // Running the script failed; bail out.
      return false;
    }
    return true;
  }


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


void V8_JS::LogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) return;
  HandleScope scope(args.GetIsolate());
  Handle<Value> arg = args[0];
  String::Utf8Value value(arg);
  V8_JS::Log(*value);
}

void V8_JS::Log(const char* event) {
  printf("Logged: %s\n", event);
}

/*
Isolate* V8_JS::GetIsolate()
{
    qDebug() << "GetIsolate";
    return isolate_;
}
*/

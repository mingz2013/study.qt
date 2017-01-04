#include "v8_js.h"
#include <stdio.h>
#include <iostream>
#include <QDebug>

V8_JS::V8_JS(QObject *parent) :
    QObject(parent)
{
}

QString V8_JS::runJS(const char *name, int x, int y)
{
    qDebug() << "runJS";
    v8::HandleScope handle_scope(GetIsolate());
    qDebug() << "handle_scope";
    Handle<ObjectTemplate> global = ObjectTemplate::New();
    global->Set(String::New("log"), FunctionTemplate::New(LogCallback));

    v8::Handle<v8::Context> context = v8::Context::New(GetIsolate(), NULL, global);

    Context::Scope context_scope(context);
    qDebug() << "context_scope";
    context_.Reset(GetIsolate(), context);

    if (!ExecuteScript(script_))   return QString("!ExecuteScript(script_)"); // false;

    //Handle<String> process_name = String::New("Process");
    Handle<String> filename = ReadFile(name);

    if(filename.IsEmpty())  return QString("file is not exist");

    Handle<Value> val = context->Global()->Get(filename);

    if (!val->IsFunction()) return QString("!val->IsFunction()"); // false;

    Handle<Function> fun = Handle<Function>::Cast(val);

    process_.Reset(GetIsolate(), fun);

    //return true;
    const int argc = 2;

    Handle<Integer> int_x ;
    Handle<Integer> int_y ;

    int_x = Integer::New(x) ;
    int_y = Integer::New(y) ;

    Handle<Value> argv[argc] = { int_x, int_y };

    Handle<Value> result = fun->Call(context->Global(), argc, argv);
    if (result.IsEmpty()) {
        //String::Utf8Value error(try_catch.Exception());
        //Log(*error);
        std::cout << "result is empty" << std::endl;
        return QString("result is empty"); //false;
      } else {
        String::AsciiValue ascii(result);
        return QString(*ascii);
        //return true;
      }
}

bool V8_JS::ExecuteScript(Handle<String> script) {

    HandleScope handle_scope(GetIsolate());

    // We're just about to compile the script; set up an error handler to
    // catch any exceptions the script might throw.
    TryCatch try_catch;

    // Compile the script and check for errors.
    Handle<Script> compiled_script = Script::Compile(script);
    if (compiled_script.IsEmpty()) {
      String::Utf8Value error(try_catch.Exception());
      Log(*error);
      // The script failed to compile; bail out.
      return false;
    }

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


Isolate* V8_JS::GetIsolate()
{
    qDebug() << "GetIsolate";
    return isolate_;
}

#include <include/v8.h>

using namespace v8;

int main(int argc,char* argv[]){
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
  Handle<String> source =String::New("'Hello' + ', World!'");

    // 那么这里，source就已经是加载过的js文件字符串内容了，接下来V8需要对js进行编译解释。
  // Compile the source code.
  Handle<Script> script =Script::Compile(source);

  // Run the script to get the result.
  Handle<Value> result = script->Run();

  // The persistent handle needs to be eventually disposed.
  persistent_context.Dispose();

  // Convert the result to an ASCII string and print it.
  String::AsciiValue ascii(result);
  printf("%s\n",*ascii);
  return 0;
}


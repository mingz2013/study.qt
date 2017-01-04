#ifndef V8_JS_H
#define V8_JS_H

#include <QObject>
#include <include/v8.h>
#include <QString>

using namespace std;
using namespace v8;

class V8_JS : public QObject
{
    Q_OBJECT
public:
    explicit V8_JS(QObject *parent = 0);
    QString runJS(const char *name, int x, int y);

private:
    Isolate* isolate_;
    Handle<String> script_;
    Persistent<Context> context_;
    Persistent<Function> process_;

    static void LogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) ;
    static void Log(const char* event);
    static Handle<String> ReadFile(const string& name);

    Isolate* GetIsolate();
    bool ExecuteScript(Handle<String> script);
};

#endif // V8_JS_H

#ifndef V8_JS_H
#define V8_JS_H

#include <QObject>
#include <include/v8.h>
#include <QString>

using namespace v8;
using namespace std;

/**
 *JS脚本执行功能
**/
class V8_JS : public QObject
{
    Q_OBJECT
public:
    explicit V8_JS(QObject *parent = 0);
    QString runJS(const char* filename, const char * funcname,const int argc,const string argv[]);

private:


    static void LogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) ;
    static void Log(const char* event);
    static Handle<String> ReadFile(const string& name);

    //Isolate* GetIsolate();
    bool ExecuteScript(Handle<String> string);
    
};

#endif // V8_JS_H

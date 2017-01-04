#ifndef V8_JS_H
#define V8_JS_H

#include <QObject>
#include <include/v8.h>
#include <QString>

using namespace v8;
using namespace std;

class v8_js : public QObject
{
    Q_OBJECT
public:
    explicit v8_js(QObject *parent = 0);
    QString runJS(const char* name);
    
signals:
    
public slots:
    
};

#endif // V8_JS_H

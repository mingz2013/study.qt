#ifndef FORM_INFO_H
#define FORM_INFO_H

#include <QWidget>

namespace Ui {
class Form_Info;
}

class Form_Info : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form_Info(QString city,QWidget *parent = 0);
    ~Form_Info();
    
private:
    Ui::Form_Info *ui;
    QString readFile(const QString& fpath);
};

#endif // FORM_INFO_H

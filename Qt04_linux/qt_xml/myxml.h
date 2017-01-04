#ifndef MYXML_H
#define MYXML_H

#include <QWidget>

class MyXml : public QWidget
{
    Q_OBJECT
public:
    explicit MyXml(QWidget *parent = 0);

    void read_xml(QString filename);
    void create_xml(QString filename);
    void add_xmlnode(QString filename,QString rmt_name,QString ipa,QString ipb);
    void do_xml(const QString opt,QString filename);

signals:
    
public slots:
    
};

#endif // MYXML_H

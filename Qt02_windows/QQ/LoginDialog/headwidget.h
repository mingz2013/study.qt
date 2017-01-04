#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QMenu>

class HeadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HeadWidget(const QString &head, QWidget *parent = 0);
    virtual void retranslateUI();
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap backgroundPixmap;
    QPixmap headPixmap;

    QPushButton *statusButton;
    QMenu* createMenu();

    QAction *imonline;
    QAction *qme;
    QAction *away;
    QAction *busy;
    QAction *mute;
    QAction *invisible;
};

#endif // HEADWIDGET_H

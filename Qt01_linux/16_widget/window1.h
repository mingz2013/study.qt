#ifndef WINDOW1_H
#define WINDOW1_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextCodec>
#include <QTextEdit>

namespace Ui {
class Window1;
}

class Window1 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Window1(QWidget *parent = 0);
    QLabel *nickNameLabel;
    QLineEdit *nickNameEdit;
    QLabel *pswdLabel;
    QLineEdit *pswdEdit;
    QLabel *accountLabel;
    QLineEdit *accountEdit;
    QLabel *mailLabel;
    QLineEdit *mailEdit;
    QLabel *addressLabel;
    QLineEdit *addressEdit;
    QLabel *jobLabel;
    QLineEdit *jobEdit;
    QLabel *introductionLabel;
    QTextEdit *introductionEdit;
private:
    Ui::Window1 *ui;
    QVBoxLayout nickNameLayout;
    QVBoxLayout accountLayout;
    QVBoxLayout mailLayout;
    QVBoxLayout pswdLayout;
    QGridLayout gLayout;
    QVBoxLayout vLayout;
    QHBoxLayout hLayout;
    QHBoxLayout hLayout1;
signals:
public slots:
};

#endif // WINDOW1_H

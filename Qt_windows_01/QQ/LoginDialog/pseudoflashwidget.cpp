#include "pseudoflashwidget.h"

#include <Qpainter>
#include <QDir>

#include <iostream>
using namespace std;

PseudoFlashWidget::PseudoFlashWidget(const QString &dirPath, QWidget *parent) :
    BackgroundWidget(parent)
{
    QDir dir(dirPath);
    if(!dir.exists())
    {
        cout << dirPath.toStdString() << " not exist."<<endl;
    }

    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        //cout << fileInfo.filePath().toStdString()<<endl;
        pixmaps.push_back(QPixmap(fileInfo.filePath()));
    }

    if(parent)
        this->setFixedSize(parent->size());
    else
    {
        if(pixmaps.size() > 0)
            this->setFixedSize(pixmaps[0].size());
    }

    texturePixmap = QPixmap(":/background/texture").copy(10, 5, 25, this->height());

    index = 0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this,  &PseudoFlashWidget::setNext);
    timer->start(200);
}

void PseudoFlashWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmaps[index]);
    painter.drawPixmap(this->rect(), texturePixmap);
}

void PseudoFlashWidget::setNext()
{
    index++;
    if(index >= pixmaps.size())
        index = 0;

    this->update();
}

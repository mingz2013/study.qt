#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkCookie>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sendPostRequest(const QUrl &url, const QByteArray &data){
            mUrl = url;
            QNetworkRequest r(mUrl);
            mManager->post(r, data);
        }
private slots:
    void replyFinished(QNetworkReply *reply){
        if (reply->error() != QNetworkReply::NoError){
            qWarning() << "ERROR:" << reply->errorString();
            return;
        }

        QList<QNetworkCookie>  cookies = mManager->cookieJar()->cookiesForUrl(mUrl);
        qDebug() << "COOKIES for" << mUrl.host() << cookies;

        qDebug() << reply->readAll();
    }

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QNetworkAccessManager *mManager;
    QUrl mUrl;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

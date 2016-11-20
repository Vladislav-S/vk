#ifndef VKCONNECT_H
#define VKCONNECT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>



class vkConnect: public QObject
{
    Q_OBJECT
public:
    explicit vkConnect();
    ~vkConnect() = default;

    int setManager(QNetworkAccessManager *man);

private:
    bool connected;

    QNetworkAccessManager * manager;

    QString login;
    QString pwd;
    QString token;
    QString reply;

    QJsonObject ObjectFromString(const QString& in);

};

#endif // VKCONNECT_H

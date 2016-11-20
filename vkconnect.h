#ifndef VKCONNECT_H
#define VKCONNECT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QEventLoop>

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>

#include <QLabel>

class vkConnect: public QObject
{
    Q_OBJECT
public:
    explicit vkConnect();
    ~vkConnect() = default;

    bool loginVk();

    int setUsername(QString name);
    int setPwd(QString password);
    int setManager(QNetworkAccessManager *man);

    void getUserInfo(QString _id, QLabel *_label);

private:
    bool connected;

    QNetworkAccessManager * manager;

    QString apiProtocol;

    QString version;
    QString grantType;
    QString appSecret;
    QString appId;
    QString id;
    QString username;
    QString pwd;
    QString token;
    QString reply;

    QJsonObject ObjectFromString(const QString& in);

};

#endif // VKCONNECT_H

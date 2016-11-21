#ifndef VKCONNECT_H
#define VKCONNECT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

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
    ~vkConnect();

    bool isLogin();

    int setUsername(QString name);
    int setManager(QNetworkAccessManager *man);

    QString getUserId();

    void getUserInfo(QString _id, QLabel *_label);

public slots:
    void acceptLogin(QUrlQuery * query);

private:
    bool connected;
    QNetworkAccessManager * manager;

    QString apiProtocol;
    QString version;
    QString expires_in;
    QString appId;
    QString id;
    QString username;
    QString token;

    QJsonObject ObjectFromString(const QString& in);
    QJsonObject sentRequest(const QString& in);

};

#endif // VKCONNECT_H

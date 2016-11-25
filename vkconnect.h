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
    bool hasNewMsgs(const QJsonObject &obj);
    bool isCorrectLogin(const QString &str);
    bool setOnline();

    int setUsername(QString name);
    int setManager(QNetworkAccessManager *man);
    int sendMsg(const QString &_msg, const QString &_id);

    QString getUserId();
    QJsonObject friendsOnline();
    QJsonObject friendList(QString _id);
    QJsonObject lastMessages(QString last_id = "");
    QJsonObject dialogHistory(const QString & user_id);



    void getUserInfo(QString _id, QLabel *_label);
    QString getUserFLName(const QString &str);

signals:
    void replyError(const QString & str);

public slots:
    void acceptLogin(QUrlQuery * query);

private:
    bool connected;
    int msgShowCount;
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

    bool isReplyCorrect(const QJsonObject & obj);

};

#endif // VKCONNECT_H

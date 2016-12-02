#ifndef VKCONNECT_H
#define VKCONNECT_H

//#include <QFile>
//#include <QTextStream>

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
#include <QSharedPointer>
#include <QPointer>
#include <QLabel>

class vkConnect: public QObject
{
    Q_OBJECT
public:
    explicit vkConnect();
    ~vkConnect();

    ///данные для подключения установлены и актуальны?
    bool isLogin();
    ///есть новые сообщения?
    bool hasNewMsgs(const QJsonObject &obj);
    ///возвращенный url корректен?
    bool isCorrectLogin(const QString &str);
    ///установить статус пользователся "online"
    bool setOnline();

    int setUsername(QString name);
    int setManager(QPointer<QNetworkAccessManager> man);
    int sendMsg(const QString &_msg, const QString &_id);

    ///получить id пользователя
    QString getUserId();
    ///получить ссылку на фото
    QString getUserPhoto50();
    ///получить друзей онлайн
    QJsonObject friendsOnline();
    ///получить список друзей
    QJsonObject friendList(QString _id);
    ///получить последние 10 сообщений
    QJsonObject lastMessages(QString last_id = "");
    ///получить последние 50 сообщений диалога
    QJsonObject dialogHistory(const QString & user_id);


    ///получить информацию о пользователе и забить его имя в лейбл
    void getUserInfo(QString _id, QLabel *_label);
    ///получить ИМЯ ФАМИЛИЮ пользователя
    QJsonObject getUser(const QString &name);
    QJsonArray getUsers(const QJsonArray &_ids);

signals:
    ///сообщить об ошибке
    void replyError(const QString & str);

public slots:
    void acceptLogin(QUrlQuery * query);

private:
    bool connected;
    int msgShowCount;
    QPointer<QNetworkAccessManager> manager;
    //QNetworkAccessManager * manager;
    QString apiProtocol;
    QString version;
    QString expires_in;
    QString appId;
    QString id;
    QString username;
    QString token;
    QString photo_50;

    ///получить QJsonObject из строки
    QJsonObject ObjectFromString(const QString& in);
    ///отправить запрос и получить ответ. in -  url
    QJsonObject sentRequest(const QString& in);
    ///ответ нас устраивает?
    bool isReplyCorrect(const QJsonObject & obj);

};

#endif // VKCONNECT_H

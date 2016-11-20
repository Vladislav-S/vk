#include "vkconnect.h"

//https://api.vk.com/method/users.get?user_ids=210700286&fields=bdate&v=5.60

//https://oauth.vk.com/token?grant_type=password&client_id=1914441&client_secret=***&username=***&password=***&v=5.60&2fa_supported=1
vkConnect::vkConnect()
{
    connected = false;
    version = "5.60";
    apiProtocol = "https://api.vk.com/method/";
    grantType = "password";
    appSecret = "2FlYYtIFenpnA0OXieBP";
    appId = "5167666";
}

bool vkConnect::loginVk(){
    if(connected) return true;
    if(username.isEmpty() || pwd.isEmpty() || version.isEmpty()
            || appId.isEmpty() || appSecret.isEmpty()
            || grantType.isEmpty()) return false;
    QString loginStr = QString("https://oauth.vk.com/token?grant_type=%1&client_id=%2&client_secret=%3&username=%4&password=%5&v=%6");
    loginStr = loginStr.arg(grantType, appId, appSecret, username, pwd, version);

    qDebug() << loginStr;

    QUrl url(loginStr);
    QNetworkRequest request(url);

    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        qDebug() <<  reply->errorString();
        reply->deleteLater();
        return false;
    }

    QByteArray content = reply->readAll();

    QString  str = QString::fromUtf8(content.data(), content.size());

    qDebug() << str << endl;
    //QJsonObject  jobj  =  ObjectFromString(str);
    return true;

}

void vkConnect::getUserInfo(QString _id, QLabel * _label){
    QString method = "users.get";
    QString requestStr = QString("%1%2?user_ids=%3&v=%4").arg(apiProtocol, method, _id, version);
    QUrl reqUrl(requestStr);
    QNetworkRequest request((reqUrl));

    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        _label->setText(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray content = reply->readAll();

    QString  str = QString::fromUtf8(content.data(), content.size());

    QJsonObject  jobj  =  ObjectFromString(str);

    QString normstr = "";

    normstr += jobj["response"].toArray().at(0).toObject()["first_name"].toString();

    _label->setText(normstr);

    reply->deleteLater();

    qDebug() << requestStr;
}

int vkConnect::setManager(QNetworkAccessManager *man){
    manager = man;
    return 1;
}

int vkConnect::setUsername(QString name){
    username = name;
}

int vkConnect::setPwd(QString password){
    pwd = password;
}

QJsonObject vkConnect::ObjectFromString(const QString &in){
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object" << endl;
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" << in << endl;
    }

    return obj;
}

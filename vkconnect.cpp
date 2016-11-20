#include "vkconnect.h"

//https://api.vk.com/method/users.get?user_ids=210700286&fields=bdate&v=5.60

vkConnect::vkConnect()
{
    connected = false;
    version = "5.60";
    apiProtocol = "https://api.vk.com/";
    grantType = "password";
    appSecret = "2FlYYtIFenpnA0OXieBP";
    appId = "5167666";
}


void vkConnect::getUserInfo(QString _id, QLabel * _label){
    QString method = "method/users.get";
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

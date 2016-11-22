#include "vkconnect.h"

//https://api.vk.com/method/users.get?user_ids=210700286&fields=bdate&v=5.60

//https://oauth.vk.com/token?grant_type=password&client_id=1914441&client_secret=***&username=***&password=***&v=5.60&2fa_supported=1
vkConnect::vkConnect()
{
    connected = false;
    version = ("5.60");
    apiProtocol = ("https://api.vk.com/method/");
    appId = ("5167666");

}

vkConnect::~vkConnect(){

}

void vkConnect::acceptLogin(QUrlQuery *query){

 token = (query->queryItemValue("access_token"));
 id = (query->queryItemValue("user_id"));
 expires_in = (query->queryItemValue("expires_in"));
 connected = true;
//TODO: emit signal to widget, to give info
}


bool vkConnect::isLogin(){
    return connected;
}

QString  vkConnect::getUserId(){
    return id;
}



QJsonObject vkConnect::sentRequest(const QString &in){
    QUrl url(in);
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        qDebug() <<  reply->errorString();
        reply->deleteLater();
        return QJsonObject();
    }
    QByteArray content = reply->readAll();

    QString  str = QString::fromUtf8(content.data(), content.size());

    qDebug() << str << endl;
    QJsonObject  jobj  =  ObjectFromString(str);

    reply->deleteLater();
    return jobj;

}

QJsonObject vkConnect::friendsOnline(){
    QString method = "friends.getOnline";
    QString requestStr = QString("%1%2?v=%3&access_token=%4").arg(apiProtocol, method, version, token);
    QJsonObject obj = sentRequest(requestStr);
    qDebug() << obj;
    return obj;

}

void vkConnect::getUserInfo(QString  _id, QLabel * _label){
    QString method = "users.get";
    QString requestStr = QString("%1%2?user_ids=%3&v=%4").arg(apiProtocol, method, _id, version);

    QJsonObject jobj =  sentRequest(requestStr);

    QString normstr = "";

    normstr += jobj["response"].toArray().at(0).toObject()["first_name"].toString();

    _label->setText(normstr);

    qDebug() << requestStr;
}

int vkConnect::setManager(QNetworkAccessManager *man){
    manager = man;
    return 1;
}

int vkConnect::setUsername(QString  name){
    if(name.isEmpty()) return -1;
    username = name;
    return 1;
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

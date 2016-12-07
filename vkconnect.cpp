#include "vkconnect.h"

//https://api.vk.com/method/users.get?user_ids=210700286&fields=bdate&v=5.60

//https://oauth.vk.com/token?grant_type=password&client_id=1914441&client_secret=***&username=***&password=***&v=5.60&2fa_supported=1
vkConnect::vkConnect()
{
    connected = false;
    version = ("5.60");
    apiProtocol = ("https://api.vk.com/method/");
    appId = ("5167666");
    msgShowCount = 50;

}

vkConnect::~vkConnect(){
    //manager.clear();
}

QJsonObject vkConnect::friendList(QString _id){
    if(!connected) return QJsonObject();
    QString method = "friends.get";
    QString requestStr = QString("%1%2?order=hints&user_id=%3&v=%4&access_token=%5").arg(apiProtocol, method, _id, version, token);
    QJsonObject obj = sentRequest(requestStr);
    obj = obj["response"].toObject();
    //qDebug() << obj;
    return obj;
}

QJsonObject vkConnect::lastMessages(QString last_id){
    if(!connected) return QJsonObject();

    QString method = "messages.get";
    QString requestStr;

    if(last_id.isEmpty())
        requestStr = QString("%1%2?count=%3&out=0&v=%4&access_token=%5").arg(apiProtocol, method, QString::number(msgShowCount-40), version, token);
    if(!last_id.isEmpty())
        requestStr = QString("%1%2?count=%3&out=0&v=%4&last_message_id=%6&access_token=%5").arg(apiProtocol, method, QString::number(msgShowCount-40), version, token, last_id);

    QJsonObject obj = sentRequest(requestStr);
    //qDebug() << requestStr;
    return obj;
}

QJsonObject vkConnect::dialogHistory(const QString &user_id)
{
    if(!connected) return QJsonObject();

    QString method = "messages.getHistory";
    QString requestStr = QString("%1%2?count=%6&user_id=%3&v=%4&access_token=%5").arg(apiProtocol, method, user_id, version, token, QString::number(msgShowCount));
    QJsonObject obj = sentRequest(requestStr);
    //qDebug() << obj;

    return obj["response"].toObject();
}


//slot
void vkConnect::acceptLogin(QUrlQuery *query){

 token = (query->queryItemValue("access_token"));
 //qDebug() << "token: " << token;
 id = (query->queryItemValue("user_id"));
 expires_in = (query->queryItemValue("expires_in"));
 connected = true;
 QJsonObject user_data = getUser(id);
 photo_50 = user_data["photo_50"].toString();
 //TODO: emit signal to widget, to give info
}

bool vkConnect::isLogin(){
    if(!token.isEmpty() && connected && !version.isEmpty() &&!expires_in.isEmpty())
        return true;
    return false;
}

bool vkConnect::hasNewMsgs(const QJsonObject &obj)
{
    return !obj["response"].toObject()["items"].toArray().isEmpty();
}

bool vkConnect::isCorrectLogin(const QString &str)
{
    //TODO
    QUrl url(str);
    QUrlQuery urlQ(url);

    if(urlQ.isEmpty() || !urlQ.hasQueryItem("access_token") || !urlQ.hasQueryItem("expires_in")
            || !urlQ.hasQueryItem("user_id")) return false;

    return true;
}

bool vkConnect::setOnline()
{
    if(!connected) return false;

    QString method = "account.setOnline";
    QString requestStr = QString("%1%2?access_token=%3").arg(apiProtocol, method, token);
    QJsonObject obj = sentRequest(requestStr);
    //qDebug() << obj;
    return false;

}


QString  vkConnect::getUserId(){
    return id;
}

QString vkConnect::getUserPhoto50()
{
    return photo_50;
}



QJsonObject vkConnect::sentRequest(const QString &in){

    QUrl url(in);
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        
        emit replyError(reply->errorString());
        reply->deleteLater();
        return QJsonObject();
    }
    QByteArray content = reply->readAll();

    QString  str = QString::fromUtf8(content.data(), content.size());

    
    QJsonObject  jobj  =  ObjectFromString(str);
    
    isReplyCorrect(jobj);
    reply->deleteLater();
    return jobj;

}

bool vkConnect::isReplyCorrect(const QJsonObject &obj)
{
    if(!obj["error"].isObject()) return true;
    connected = false;
    emit replyError(obj["error"].toObject()["error_msg"].toString());
    return false;
}

QJsonObject vkConnect::friendsOnline(){
    QString method = "friends.getOnline";
    QString requestStr = QString("%1%2?v=%3&access_token=%4").arg(apiProtocol, method, version, token);
    QJsonObject obj = sentRequest(requestStr);
    
    return obj;

}

void vkConnect::getUserInfo(QString  _id, QLabel * _label){
    QString method = "users.get";
    QString requestStr = QString("%1%2?user_ids=%3&v=%4").arg(apiProtocol, method, _id, version);

    QJsonObject jobj =  sentRequest(requestStr);

    QString normstr = "";

    normstr += jobj["response"].toArray().at(0).toObject()["first_name"].toString();

    _label->setText(normstr);

    //qDebug() << requestStr;
}

QJsonObject vkConnect::getUser(const QString &str)
{
    QString method = "users.get";
    QString requestStr = QString("%1%2?user_ids=%3&fields=photo_50,city,verified&v=%4&access_token=%5").arg(apiProtocol, method, str, version, token);
    QJsonObject jobj =  sentRequest(requestStr);
    //qDebug() << jobj;
    return jobj["response"].toArray()[0].toObject();
}

QJsonArray vkConnect::getUsers(const QJsonArray &_ids)
{
    QString method = "users.get";
    QString _idsStr;
    for(int i{0}; i < _ids.size(); i++){
        if(i != 0) _idsStr += ",";
        _idsStr += QString::number(_ids[i].toInt());
    }
    //qDebug() << "idsStr:" <<_idsStr;
    QString requestStr = QString("%1%2?user_ids=%3&v=%4").arg(apiProtocol, method, _idsStr, version);
    QJsonObject jobj =  sentRequest(requestStr);
    //qDebug() << jobj;
    return jobj["response"].toArray();

}

int vkConnect::setManager(QPointer<QNetworkAccessManager> man){
    manager = man;
    return 1;
}

int vkConnect::sendMsg(const QString &_msg, const QString &_id)
{
    QString method = "messages.send";
    QString requestStr = QString("%1%2?user_id=%3&message=%4&v=%5&access_token=%6").arg(apiProtocol, method, _id, _msg, version, token);
    QJsonObject jobj =  sentRequest(requestStr);
    //qDebug() << jobj;
    return  jobj["response"].toInt();
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

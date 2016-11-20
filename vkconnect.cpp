#include "vkconnect.h"

vkConnect::vkConnect()
{
    connected = false;

}

int vkConnect::setManager(QNetworkAccessManager *man){
    manager = man;
    qDebug() << manager;
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

    qDebug() << "function passed " << in << obj << endl;
    return obj;
}

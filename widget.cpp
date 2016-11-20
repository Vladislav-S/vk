#include "ui_widget.h"
#include "widget.h"
//класс окна
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //инициализируем менеджер доступа к сети
    manager = new QNetworkAccessManager(this);
    //qDebug() << manager;
    //потихоньку инкапсулируем функционал
    vk = new vkConnect();
    vk->setManager(manager);
}

Widget::~Widget()
{
    delete ui;
}

//тестовый слот для получения строки адреса и вызова метода get
void Widget::on_submit_login_clicked()
{
    QString str = ui->lineEdit_test->text();
    QNetworkRequest * req = new QNetworkRequest(QUrl(str));

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinTest(QNetworkReply *)));

    manager->get(*req);
}


//функция для обработки ответа на запрос
void Widget::replyFinTest(QNetworkReply  *reply){

    //если ошибка
    if(reply->error() != QNetworkReply::NoError){
        ui->login_log->setText(reply->errorString());
        reply->deleteLater();
        return;
    }

    //если все хорошо, то вытаскиваем массив битов из ответа
    QByteArray content = reply->readAll();
    // преобразуем его в строку
    QString  str = QString::fromUtf8(content.data(), content.size());

    //выводим текст
    QString normstr = "";

    //преобразуем данные в json тип
    QJsonObject  jobj  =  ObjectFromString(str);

    //вывод даты
    normstr += jobj["response"].toArray().at(0).toObject()["bdate"].toString();
    //normstr += jobj["response"];

    ui->login_log->setText(normstr);

    //в консоль еще
    //qDebug() << jobj.size() << " " << jobj["response"].toArray().at(0).toObject()["bdate"].toString();
    reply->deleteLater();
}



//функция для преобразования строки в json объект
QJsonObject Widget::ObjectFromString(const QString& in)
{
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

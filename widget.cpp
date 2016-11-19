#include "widget.h"
#include "ui_widget.h"

//класс окна
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //инициализируем менеджер доступа к сети
    manager = new QNetworkAccessManager(this);
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
    ui->login_log->setText(str);

    //в консоль ещеы
    qDebug() << str;
    reply->deleteLater();
}

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
    //QString str = ui->lineEdit_test->text();
    //vk->getUserInfo(str, ui->login_log);

    QString username = ui->login_edit->text();
    QString pwd = ui->password_edit->text();

    vk->setUsername(username);
    vk->setPwd(pwd);

    vk->loginVk();
}


/*

 connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinTest(QNetworkReply *)));

*/

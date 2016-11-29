#include "ui_widget.h"
#include "widget.h"

//класс окна
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    currentIndex = 0;

    //инициализируем менеджер доступа к сети
    manager = new QNetworkAccessManager(this);

    vk = new vkConnect();
    vk->setManager(manager);

    w_log = new w_login(this, vk);
    form = new Form(this, vk);

    l = new QStackedLayout(this);

    l->addWidget(w_log);
    l->addWidget(form);

    setLayout(l);

    l->setCurrentIndex(currentIndex);


    connect(w_log, SIGNAL(login_succesfull()), this, SLOT(on_login()));
    connect(this, SIGNAL(ready()), form, SLOT(ready()));
    connect(vk, SIGNAL(replyError(QString)), this, SLOT(on_error(QString)));

    //TODO - перевести функционал в vkConnect
//    QFile file(":/userdata.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//            return;
//    QByteArray barray = file.readAll();
//    QString str = QString::fromUtf8(barray);
//    qDebug() << barray;
//    qDebug() << str;

}

void Widget::on_login(){

    qDebug() << "logged";
    currentIndex = 1;
    l->setCurrentIndex(currentIndex);
    this->resize(form->getW(), form->getH());
    emit ready();
}

void Widget::on_error(const QString &string)
{
    qDebug() << string;
    errorD = new error_dialog(this, string);

    connect(errorD, SIGNAL(on_ok()), this, SLOT(close()));

    errorD->exec();
    //QThread::sleep(100000);
}

Widget::~Widget()
{
    delete ui;
    delete manager;
    delete vk;
    delete l;
    delete w_log;
    delete form;
    delete errorD;
}

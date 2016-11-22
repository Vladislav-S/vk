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

}

void Widget::on_login(){

    qDebug() << "logged";
    currentIndex = 1;
    l->setCurrentIndex(currentIndex);
}

Widget::~Widget()
{
    delete ui;
    delete manager;
    delete vk;
    delete l;
    delete w_log;
    delete form;
}

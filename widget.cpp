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

    l = new QStackedLayout(this);

    l->addWidget(w_log);

    setLayout(l);

    l->setCurrentIndex(currentIndex);
}

Widget::~Widget()
{
    delete ui;
    delete manager;
    delete vk;
    delete l;
    delete w_log;
}

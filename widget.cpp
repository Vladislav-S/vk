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

    loginD = new loginDialog();
    connect(loginD, SIGNAL(sentQUrl(QUrlQuery*)), vk, SLOT(acceptLogin(QUrlQuery*)));
    connect(loginD, SIGNAL(finished(int)), this, SLOT(on_Widget_destroyed()));
}

Widget::~Widget()
{
    delete ui;
    delete loginD;
    delete manager;
    delete vk;
}


void Widget::on_button_login_clicked()
{
    if(!vk->isLogin()){
        loginD->exec();
        QString  id(vk->getUserId());
        vk->getUserInfo(id, ui->label_current_user);
    }
    else{
        //TODO: sent signal to draw window
    }
}

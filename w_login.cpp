#include "w_login.h"
#include "ui_w_login.h"

w_login::w_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::w_login)
{
    ui->setupUi(this);

    loginD = new loginDialog(this);

}

w_login::w_login(QWidget *parent, vkConnect * _vk) :
    QWidget(parent),
    ui(new Ui::w_login)
{
    ui->setupUi(this);
    vk = _vk;
    loginD = new loginDialog(this);

    connect(loginD, SIGNAL(sentQUrl(QUrlQuery*)), vk, SLOT(acceptLogin(QUrlQuery*)));

}

w_login::~w_login()
{
    delete ui;
    delete loginD;
}

void w_login::on_b_login_clicked()
{
    if(!vk->isLogin()){
        loginD->exec();
        QString  id(vk->getUserId());
        vk->getUserInfo(id, ui->label_current_user_name);
        emit login_succesfull();
    }
    else{
        //TODO: sent signal to draw window
    }
}

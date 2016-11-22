#ifndef W_LOGIN_H
#define W_LOGIN_H

#include <QWidget>
#include "vkconnect.h"
#include "logindialog.h"

namespace Ui {
class w_login;
}

class w_login : public QWidget
{
    Q_OBJECT

public:
    explicit w_login(QWidget *parent = 0);
    w_login(QWidget *parent = 0, vkConnect * _vk = 0);
    ~w_login();

private slots:
    void on_b_login_clicked();

private:
    Ui::w_login *ui;
    vkConnect * vk;
    loginDialog * loginD;
};

#endif // W_LOGIN_H

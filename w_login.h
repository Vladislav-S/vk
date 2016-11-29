#ifndef W_LOGIN_H
#define W_LOGIN_H

#include <QWidget>
#include <QInputDialog>
#include <QWebEngineView>
#include <QUrlQuery>

#include "vkconnect.h"

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

signals:
    void login_succesfull();
    void sentQUrl(QUrlQuery* _qurl);
private slots:
    void urlChanged(const QUrl &_url);
    void on_b_web_login_clicked();

private:
    Ui::w_login *ui;
    vkConnect * vk;
    QWebEngineView * web;
    QUrlQuery * urlq;

};

#endif // W_LOGIN_H

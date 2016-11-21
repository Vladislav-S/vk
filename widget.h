#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>

//#include <QList>
#include "vkconnect.h"
#include "logindialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:


    void on_button_login_clicked();

private:
    loginDialog * loginD;
    Ui::Widget *ui;
    QNetworkAccessManager * manager;
    vkConnect * vk;

protected:

};

#endif // WIDGET_H

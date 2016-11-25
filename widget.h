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
#include <QStackedLayout>
#include <QThread>

#include "vkconnect.h"
#include "form.h"
#include "w_login.h"
#include "form.h"
#include "error_dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void on_login();
    void on_error(const QString & string);
signals:
    void ready();
private:
    int currentIndex;

    Ui::Widget *ui;
    QNetworkAccessManager * manager;
    vkConnect * vk;
    QStackedLayout * l;
    w_login * w_log;
    Form * form;
    error_dialog * errorD;
protected:

};

#endif // WIDGET_H

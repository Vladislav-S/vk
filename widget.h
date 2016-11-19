#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>


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
    void replyFinTest(QNetworkReply *reply);

    //void replyFinished(const QNetworkReply &reply);

    void on_submit_login_clicked();

private:
    Ui::Widget *ui;
    QNetworkAccessManager * manager;
};

#endif // WIDGET_H

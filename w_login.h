#ifndef W_LOGIN_H
#define W_LOGIN_H

#include <QWidget>
#include <QInputDialog>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QWebEngineCookieStore>
#include <QUrlQuery>
#include <QString>
#include <QCheckBox>
#include <QPointer>

#include "vkconnect.h"

namespace Ui {
class w_login;
}

/*!
 * \brief The w_login class
 *
 * класс отвечающий за логинизацию
 */
class w_login : public QWidget
{
    Q_OBJECT

public:
    explicit w_login(QWidget *parent = 0);
    w_login(QWidget *parent = 0, QSharedPointer<vkConnect> _vk = QSharedPointer<vkConnect>());
    ~w_login();

signals:
    ///если успешно подключились
    void login_succesfull();
    ///отправить объекту vk полученные данные
    void sentQUrl(QUrlQuery* _qurl);
    ///изменился размер окна
    void resized(const int &_width, const int &_height);
private slots:
    ///если в web изменилась url
    void urlChanged(const QUrl &_url);
    ///если нажата кнопка login
    void on_b_web_login_clicked();

private:
    Ui::w_login *ui;
    QSharedPointer<vkConnect> vk;

    ///для отображения веб страницы логинизации
    QWebEngineView * web;

};

#endif // W_LOGIN_H

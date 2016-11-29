#include "w_login.h"
#include "ui_w_login.h"

w_login::w_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::w_login)
{
    ui->setupUi(this);
}

//основной конструктор
w_login::w_login(QWidget *parent, vkConnect * _vk) :
    QWidget(parent),
    ui(new Ui::w_login)
{
    ui->setupUi(this);
    vk = _vk;
    connect(this, SIGNAL(sentQUrl(QUrlQuery*)), vk, SLOT(acceptLogin(QUrlQuery*)));

}
w_login::~w_login()
{
    delete ui;
    delete urlq;
    //web->deleteLater();

}


//когда в web изменилась страница
void w_login::urlChanged(const QUrl & _url)
{
    if(_url.toString().indexOf("access_token=") != -1)
    {
        web->close();
        web->deleteLater();
        QString str = _url.toString().replace("#", "?");
        QUrl nurl(str);
        urlq = new QUrlQuery(_url);
        QUrlQuery querry(nurl);

        emit sentQUrl(&querry); //отправить данные в vk
        //TODO : проверить наличие данных в vk
        if(vk->isLogin()){
            vk->setOnline();
            emit login_succesfull();
        }

    }
    else return;

}

void w_login::on_b_web_login_clicked()
{
    QUrl url = QUrl("https://oauth.vk.com/authorize?client_id=5167666&redirect_uri=https://oauth.vk.com/blank.html&scope=friends,wall,groups,messages,photos,audio,stats&response_type=token&v=5.60");

    web = new QWebEngineView(this);
    connect(web, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
    web->show();
    web->load(url);
    emit resized(web->width(), web->height()); //подогнать под размер страницы
    if(ui->cb_new->checkState() == Qt::Checked) //если новый юзер
        web->page()->profile()->cookieStore()->deleteAllCookies();
    }

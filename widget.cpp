#include "ui_widget.h"
#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    currentIndex = 0;

    //инициализируем менеджер доступа к сети
    //manager = new QNetworkAccessManager(this);
    //manager.reset(new QNetworkAccessManager(this));
    manager =  QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager(this));
    //инициализируем класс подключения к серверу вк
    vk =  QSharedPointer<vkConnect>(new vkConnect());
    vk->setManager(manager);

    //иннциализируем окна
    w_log = new w_login(this, vk);
    form = new Form(this, vk);

    //иниц. хранилища окон
    l = new QStackedLayout(this);
    l->addWidget(w_log);
    l->addWidget(form);
    //устанавливаем хранилище в качестве текущего
    setLayout(l);
    //устанавливаем и отображаем текущее окно
    l->setCurrentIndex(currentIndex);


    connect(w_log, SIGNAL(login_succesfull()), this, SLOT(on_login())); //если успешно подключились в w_log
    connect(w_log, SIGNAL(resized(int,int)), this, SLOT(on_content_resized(int,int))); //если изменился размер в w_log
    connect(this, SIGNAL(ready()), form, SLOT(ready())); //если данные готовы для вывода в form
    connect(vk.data(), SIGNAL(replyError(QString)), this, SLOT(on_error(QString))); //если ошибка

}

//в случае успешного подключения отображает сообщает окну чата о готовности, окно затем отображается
void Widget::on_login(){

    qDebug() << "logged";
    currentIndex = 1;
    l->setCurrentIndex(currentIndex);
    this->resize(form->getW(), form->getH());
    emit ready();
}

//слот - держатель ошибок, в конце уничтожает главное окно
void Widget::on_error(const QString &string)
{
    qDebug() << string;
    errorD = new error_dialog(this, string);

    connect(errorD, SIGNAL(on_ok()), this, SLOT(close()));

    errorD->exec();
    //QThread::sleep(100000);
}

//сигнал - когда изменен размер окна
void Widget::on_content_resized(const int &_width, const int &_height)
{
    this->resize(_width, _height);
}

void Widget::closeEvent(QCloseEvent *event)
{
    w_log->close();
    form->close();
    QWidget::closeEvent(event);
}

Widget::~Widget()
{
    delete ui;
    //delete manager;
    //delete vk;
    vk.clear();
    l.clear();
    delete w_log;
    delete form;
    if(errorD != nullptr)
        delete errorD;
}

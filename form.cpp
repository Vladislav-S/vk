#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    w = this->width();
    h = this->height();

    ui->l_contacts->setMouseTracking(true);
}

Form::Form(QWidget *parent, vkConnect * _vk) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    vk = _vk;
    w = this->width();
    h = this->height();
}

Form::~Form()
{
    delete ui;
}

int Form::getW(){
    return w;
}

int Form::getH(){
    return h;
}

void Form::ready()
{
    friends = vk->friendList(vk->getUserId());

    int count = friends["count"].toInt();

    QJsonArray friendIds = friends["items"].toArray();

    //qDebug() << QString::number(friendIds[0].toInt());

    for(int i = 0; i < count; i++){
        QString FLName;
        FLName = vk->getUserFLName(QString::number(friendIds[i].toInt()));
        ui->l_contacts->addItem(FLName);

        QString statusTip = QString::number(friendIds[i].toInt());
        ui->l_contacts->item(i)->setStatusTip(statusTip);
        //qDebug() << ui->l_contacts->item(i)->statusTip();
    }

    //TODO: получение последних 200ста сообщений и хранение их в контейнере


}

void Form::on_l_contacts_itemActivated(QListWidgetItem *item)
{
    //ui->t_view->setText(item->statusTip());
    //ui->t_view->clear();
    currentDiaolg.clear();
    QJsonObject obj =  vk->dialogHistory(item->statusTip());
    QJsonArray msgArray = obj["items"].toArray();

    int out;
    QString delimetr = "------------------------\n";
    QString from = item->text();
    QString body;
    for(int i = 0; i < msgArray.size(); i++){
        body = msgArray[i].toObject()["body"].toString();
        currentDiaolg += delimetr;
        out = msgArray[i].toObject()["out"].toInt(); //0 - resieved, 1-sended
        if(!out) currentDiaolg += "from " + from + "\n" + delimetr;
        else currentDiaolg += "my\n"+delimetr;

        currentDiaolg += body + "\n";
    }
    ui->t_view->setText(currentDiaolg);

}

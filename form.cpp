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

    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(checkNewMsg()));


}

Form::Form(QWidget *parent, QSharedPointer<vkConnect> _vk) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    vk = _vk;
    w = this->width();
    h = this->height();

    ui->t_edit->setPB(ui->b_sent);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(checkNewMsg()));

    //ui->chat->page()->setScrollBar

    //--------BASIC---------
    QFile fbhtml(":/basichtml.html");
    if (!fbhtml.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    QByteArray barray = fbhtml.readAll();
    basicHTML = QString::fromUtf8(barray);
    fbhtml.close();

    //------STYLE--------
    QFile fStyle(":/style.css");
    if (!fStyle.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fStyle.readAll();
    CSS = QString::fromUtf8(barray);
    fStyle.close();

    //------MENU-------
    QFile fMenu(":/menu.html");
    if (!fMenu.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fMenu.readAll();
    chatMenu = QString::fromUtf8(barray);
    fMenu.close();

    //-----OTHER-------
    QFile fOther(":/other.html");
    if (!fOther.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fOther.readAll();
    chatOther = QString::fromUtf8(barray);
    fOther.close();

    //------SELF-------
    QFile fSelf(":/self.html");
    if (!fSelf.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fSelf.readAll();
    chatSelf = QString::fromUtf8(barray);
    fSelf.close();

}


Form::~Form()
{
    delete ui;
    delete timer;
}

int Form::getW(){
    return w;
}

int Form::getH(){
    return h;
}



void Form::ready()
{
    if(!vk->isLogin()) return;
    friends = vk->friendList(vk->getUserId());

    int progress = 0;
    int count = friends["count"].toInt();
    ui->progressBar->setMaximum(count);


    QJsonArray friendIds = friends["items"].toArray();
    QJsonArray friendArray = vk->getUsers(friendIds);
    //qDebug() << friendArray;
    for(int i = 0; i < count; i++){
        QString FLName;
        FLName = friendArray[i].toObject()["first_name"].toString() + " " +friendArray[i].toObject()["last_name"].toString();
        ui->l_contacts->addItem(FLName);

        QString statusTip = QString::number(friendArray[i].toObject()["id"].toInt());
        ui->l_contacts->item(i)->setStatusTip(statusTip);
        progress++;
        ui->progressBar->setValue(progress);
    }

    //TODO: получение последних 10 сообщений и хранение их в контейнере
    lastMessages = vk->lastMessages();
    lastMsgID = QString::number(lastMessages["response"].toObject()["items"].toArray()[0].toObject()["id"].toInt());


    timer->start(4000);


}

void Form::on_l_contacts_itemActivated(QListWidgetItem *item)
{
    currentDiaolg.clear();
    chatMiddle.clear();
    QJsonObject obj =  vk->dialogHistory(item->statusTip());
    QJsonArray msgArray = obj["items"].toArray();
    QString time;
    QString photo_130 = "<img src=\"%1\" alt=\"\">";
    QJsonObject other = vk->getUser(ui->l_contacts->currentItem()->statusTip());

    //qDebug() << msgArray;
    int out;
    QString from = item->text();
    QString body;

    for(int i = msgArray.size()-1; i > -1 ; i--){
        QString photo;
        if(!msgArray[i].toObject()["photo_130"].toString().isEmpty())
            photo = photo_130.arg(msgArray[i].toObject()["photo_130"].toString());
        qDebug() << photo;
        body = msgArray[i].toObject()["body"].toString();

        time = QDateTime::fromTime_t(msgArray[i].toObject()["date"].toInt()).toString();
        //qDebug() << time;
        out = msgArray[i].toObject()["out"].toInt(); //0 - resieved, 1-sended
        if(!out) {
            chatMiddle += chatOther.arg(body, time, other["photo_50"].toString(), photo);
        }
        else {
            chatMiddle += chatSelf.arg(body, time, vk->getUserPhoto50(), photo);

        }



    }
    chatHTML = basicHTML.arg(CSS, chatMenu.arg(from, "", chatMiddle));
    ui->chat->setHTML(chatHTML);
}

void Form::on_b_sent_clicked()
{
    QString jsScript = "document.getElementsByClassName('chat').innerHTML = \"%1\"";
    QString msg = ui->t_edit->toPlainText();
    //jsScript = jsScript.arg(chatSelf.arg(msg, QDateTime(QDateTime::currentDateTime()).toString(), vk->getUserPhoto50()));

    vk->sendMsg(msg, ui->l_contacts->currentItem()->statusTip());

    ui->t_edit->clear();

    int index = chatHTML.indexOf("</ol>");
    ui->chat->setHTML(chatHTML.insert(index, chatSelf.arg(msg, QDateTime(QDateTime::currentDateTime()).toString(), vk->getUserPhoto50(), "")));

    //ui->chat->page()->runJavaScript(jsScript, );

}

void Form::on_progressBar_valueChanged(int value)
{
    if(value == ui->progressBar->maximum()) ui->progressBar->hide();
}

void Form::checkNewMsg()
{

    lastMessages = vk->lastMessages(lastMsgID);
    if(!vk->hasNewMsgs(lastMessages)) return;

    QJsonArray array = lastMessages["response"].toObject()["items"].toArray();
    lastMsgID = QString::number(array[0].toObject()["id"].toInt());
    QListWidgetItem * item;

    for(int i = 0; i < array.size(); i++){
        item = serchById(QString::number(array[i].toObject()["user_id"].toInt()));
        emit ui->l_contacts->itemActivated(item);
    }

}

QListWidgetItem * Form::serchById(const QString &id)
{
    int number = ui->l_contacts->count();
    for(int i{0}; i < number; i++){
        if(ui->l_contacts->item(i)->statusTip() == id) return ui->l_contacts->item(i);
    }
    return Q_NULLPTR;
}

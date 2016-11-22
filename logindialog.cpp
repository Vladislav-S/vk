#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

loginDialog::~loginDialog()
{
    delete ui;

}

void loginDialog::on_pushButton_clicked()
{

    QUrl url = QUrl("https://oauth.vk.com/authorize?client_id=5167666&redirect_uri=https://oauth.vk.com/blank.html&scope=friends,wall,groups,messages,photos,audio,stats&response_type=token&v=5.60");
    QDesktopServices::openUrl(url);
}

void loginDialog::on_buttonBox_accepted()
{
    if(ui->lineEdit->text().isEmpty()) return;
    urlStr = ui->lineEdit->text();
    url = QUrl(urlStr);
    url = url.toString().replace("#", "?");
    QUrlQuery * urlq = new QUrlQuery(url);

    emit sentQUrl(urlq);
}



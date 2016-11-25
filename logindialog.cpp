#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    ui->buttonBox->setEnabled(false);
}

loginDialog::~loginDialog()
{
    delete ui;

}

//когда нажата кнопка авторизации
void loginDialog::on_pushButton_clicked()
{

    QUrl url = QUrl("https://oauth.vk.com/authorize?client_id=5167666&redirect_uri=https://oauth.vk.com/blank.html&scope=friends,wall,groups,messages,photos,audio,stats&response_type=token&v=5.60");
    QDesktopServices::openUrl(url);
}


//если ОК
void loginDialog::on_buttonBox_accepted()
{
    //если строка пустая
    if(ui->lineEdit->text().isEmpty()) return;
    urlStr = ui->lineEdit->text();
    url = QUrl(urlStr);
    //url = url.toString().replace("#", "?");
    QUrlQuery * urlq = new QUrlQuery(url);

    emit sentQUrl(urlq);
}



void loginDialog::on_lineEdit_textChanged(const QString &arg1)
{
    bool correct = false;
    QString str = arg1;
    str = str.remove(" ").replace("#", "?");
    ui->lineEdit->setText(str);
    if(str.isEmpty()) {
        ui->l_status->setText("link is empty");
        ui->buttonBox->setEnabled(false);
        return;
    }
    if(isCorrectLogin(str)) {
        correct = true;
        ui->l_status->setText("all correct");
    }
    else{
        ui->l_status->setText("incorrect ulr recieved");
        ui->buttonBox->setEnabled(false);
        return;
    }

    if(correct){
        ui->buttonBox->setEnabled(true);
    }



}

bool loginDialog::isCorrectLogin(const QString &str)
{
    QUrl url(str);
    QUrlQuery urlQ(url);

    if(urlQ.isEmpty() || !urlQ.hasQueryItem("access_token") || !urlQ.hasQueryItem("expires_in")
            || !urlQ.hasQueryItem("user_id")) return false;

    return true;
}

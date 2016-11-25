#include "error_dialog.h"
#include "ui_error_dialog.h"

error_dialog::error_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error_dialog)
{
    ui->setupUi(this);
}

error_dialog::error_dialog(QWidget *parent, const QString &error_msg):
    QDialog(parent),
    ui(new Ui::error_dialog)
{
    ui->setupUi(this);
    ui->label->setText(error_msg);

}

error_dialog::~error_dialog()
{
    delete ui;
}

void error_dialog::on_pushButton_clicked()
{
    emit on_ok();
}

void error_dialog::on_error_dialog_destroyed()
{
    emit on_ok();
}

void error_dialog::on_error_dialog_finished(int result)
{
    emit on_ok();
}

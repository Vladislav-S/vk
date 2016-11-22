#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::Form(QWidget *parent, vkConnect * _vk) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    vk = _vk;
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    vk->friendsOnline();
}
